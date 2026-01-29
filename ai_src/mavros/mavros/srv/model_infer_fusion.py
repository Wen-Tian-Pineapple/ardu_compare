#! /usr/bin/env python

import numpy as np
import torch
import torch.nn as nn
from torch.nn.utils import spectral_norm
from mavros_msgs.msg import JAIOut
from mavros_msgs.msg import JaiRaw
import math

def throttle_value(x):
    result=1000

    if x > 0:
        result= int(60 * x + 1335)
    else:
        result= int(30 * x + 1335)
    # result=(result-1000)/1000

    return result

def thrust_value(x):
    result=3.1821e-05*x*x-0.056735*x+23.1451
    return result

def next_force(input_data,desired_accel,result):
    u_next=(desired_accel-24.03*np.sin(input_data[0])-result)/(4.5609*2*np.sin(-input_data[0]))
    return u_next

def get_accel(u_pre,input_data,result):

    a=result-4.5609*2*u_pre*np.sin(input_data[0])+24.03*np.sin(input_data[0])
    
    return a

def force_to_u(desired_force):
    c=23.1451-desired_force
    _F_desired_PWM=int((0.056735+math.sqrt(0.056735*0.056735-4*0.00001*3.1821*c))/(2*0.00001*3.1821));
    if _F_desired_PWM>1335:
        u=(_F_desired_PWM-1335)/60
    else:
        u=(_F_desired_PWM-1335)/30

    if u>1:
        u=1
    elif u<-1:
        u=-1
    
    return u
        
class FusionNet(nn.Module):
    def __init__(self):
        super(FusionNet, self).__init__()
        self.f11 = spectral_norm(nn.Linear(1, 20))
        self.bn_f11 = nn.BatchNorm1d(20)
        self.f21 = spectral_norm(nn.Linear(1, 20))
        self.bn_f21 = nn.BatchNorm1d(20)
        self.f31 = spectral_norm(nn.Linear(1, 20))
        self.bn_f31 = nn.BatchNorm1d(20)
        self.f41 = spectral_norm(nn.Linear(1, 20))
        self.bn_f41 = nn.BatchNorm1d(20)

        self.fc1 = spectral_norm(nn.Linear(80, 128))
        self.bn1 = nn.BatchNorm1d(128)
        self.fc2 = spectral_norm(nn.Linear(128, 64))
        self.bn2 = nn.BatchNorm1d(64)
        self.fc3 = spectral_norm(nn.Linear(64, 1))
        self.sigmoid = nn.Sigmoid()
        self.relu = nn.ReLU()

    def forward(self, x):
        feature1 = self.sigmoid(self.bn_f11(self.f11(x[:, 0:1])))
        feature2 = self.sigmoid(self.bn_f21(self.f21(x[:, 1:2])))
        feature3 = self.relu(self.bn_f31(self.f31(x[:, 2:3])))
        feature4 = self.relu(self.bn_f41(self.f41(x[:, 3:4])))

        f_all = torch.cat([0.1 * feature1, 0.001 * feature2, 0.1 * feature3, 3*feature4], dim=-1)

        f_all = self.relu(self.bn1(self.fc1(f_all)))
        f_all = self.relu(self.bn2(self.fc2(f_all)))
        f_all = self.fc3(f_all)

        return f_all


def sign(x):
    if x > 0:
        return 1
    elif x < 0:
        return -1
    else:
        return 0


class SegRos(object):
    def __init__(self, predictor, device):
        self.predictor = predictor
        self.device = device
        self.message_buffer = []
        self.message_subscriber = rospy.Subscriber('/mavros/jai_raw', JaiRaw, callback=self.message_callback, queue_size=1)
        self.message_publisher = rospy.Publisher('/Jai_command', JAIOut, queue_size=1)
        self.traj_subscriber=rospy.Subscriber('/Jai_traj',JAIOut,callback=self.traj_cb,queue_size=1)
        self.new_traj=JAIOut()
    def message_callback(self, msg):
        # print(msg)
        # data = np.array([msg.rol, msg.pit, msg.yaw, msg.drol, msg.dpit, msg.dyaw, msg.xa, msg.ya, msg.za, 0, msg.ul, msg.beta, msg.Thr_out])
        force=thrust_value(throttle_value(msg.Thr_out))
        data=np.array([msg.pit,msg.ul,msg.beta,force])
        sample_tensor = torch.tensor(data,dtype=torch.float).to(self.device).unsqueeze(0).view(1,-1)
        prediction = self.predictor(sample_tensor)
        # print(msg.Thr_out)
        # gradient = torch.autograd.grad(prediction,sample_tensor,grad_outputs=torch.ones_like(prediction),create_graph=True)[0]
        result=prediction.detach().cpu().numpy()[0]
        max_accelerate=5
        sample_freq=105
        u_pre=force_to_u(data[-1])
        if abs(msg.desired_dpit-msg.dpit)*105>max_accelerate :
            desired_accel=sign(msg.desired_dpit-result)*max_accelerate
            force_next=next_force(data,desired_accel,result)
            u_next=force_to_u(force_next)
            time_begin=rospy.Time.now().to_sec()
            while abs(u_pre-u_next)>0.03:
                # time_begin=rospy.Time.now().to_sec()
                u_pre=data[-1]
                

                sample_tensor = torch.tensor(data,dtype=torch.float).to(self.device).unsqueeze(0).view(1,-1)
                prediction = self.predictor(sample_tensor)
                print("INFER TIME:",rospy.Time.now().to_sec()-time_begin)
                force_next=next_force(data,desired_accel,result)
                u_next=force_to_u(force_next)
                data[-1]=force_next
                
                if(rospy.Time.now().to_sec()-time_begin>0.1):
                    print("Overtime Use PID:",result)
                    self.new_traj.u_thr=u_next
                    if self.new_traj.rc_state==2:
                        self.new_traj.rc_state=1
                    self.message_publisher.publish(self.new_traj)
                    return
                if force_next>thrust_value(1395):
                    print("OverThrust Use PID:")
                    self.new_traj.u_thr=u_next
                    if self.new_traj.rc_state==2:
                        self.new_traj.rc_state=1
                    self.message_publisher.publish(self.new_traj)
                    return

            print("Success:")
            self.new_traj.u_thr=u_next
            self.message_publisher.publish(self.new_traj)
            return
        else:
            desired_accel=(msg.desired_dpit-result)*sample_freq
            force_next=next_force(data,desired_accel,result)
            u_next=force_to_u(force_next)
            time_begin=rospy.Time.now().to_sec()
            while abs(u_pre-u_next)>0.03:
                u_pre=data[-1]
                sample_tensor = torch.tensor(data,dtype=torch.float).to(self.device).unsqueeze(0).view(1,-1)
                prediction = self.predictor(sample_tensor)
                force_next=next_force(data,desired_accel,result)
                u_next=force_to_u(force_next)
                data[-1]=force_next

                if(rospy.Time.now().to_sec()-time_begin>0.1):
                    print("Overtime Use PID:",result)
                    self.new_traj.u_thr=u_next
                    if self.new_traj.rc_state==2:
                        self.new_traj.rc_state=1
                    self.message_publisher.publish(self.new_traj)
                    return
                if force_next>thrust_value(1395):
                    print("OverThrust Use PID:")
                    self.new_traj.u_thr=u_next
                    if self.new_traj.rc_state==2:
                        self.new_traj.rc_state=1
                    self.message_publisher.publish(self.new_traj)
                    return
                
            print("Success:")
            self.new_traj.u_thr=u_next
            self.message_publisher.publish(self.new_traj)
            return


            
        

    def traj_cb(self,msg):
        self.new_traj=msg


if __name__ == '__main__':
    batchsize = 1
    # if torch.cuda.is_available():
    #     print("CUDA is available!")
    #     print("Number of GPUs:", torch.cuda.device_count())
    #     print("CUDA Device Name:", torch.cuda.get_device_name(0))
    #     print("CUDA Device Capability:", torch.cuda.get_device_capability(0))
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    model =  FusionNet().to(device)
    model_path = '/home/xxh/Doublebee/hh_layer (backup_tested)/best_model_weights.pth'
    model.load_state_dict(torch.load(model_path, map_location='cuda:0'))
    model.eval()
    print('1')
    import rospy
    rospy.init_node("seg_node")
    yolox_ros = SegRos(predictor=model,device=device)
    rospy.spin()