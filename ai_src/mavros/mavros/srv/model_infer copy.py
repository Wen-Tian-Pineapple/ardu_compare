#! /usr/bin/env python

import numpy as np
import torch
import torch.nn as nn
from torch.nn.utils import spectral_norm
from mavros_msgs.msg import JAIOut
from mavros_msgs.msg import JaiRaw


class Net(nn.Module):
    def __init__(self, depth, D_in, D_h, D_out):
        super(Net, self).__init__()
        self.depth = depth
        self.layers = nn.ModuleList()

        if depth == 1:
            self.layers.append(spectral_norm(nn.Linear(D_in, D_out)))
        else:
            self.layers.append(spectral_norm(nn.Linear(D_in, D_h)))
            self.layers.append(nn.ReLU())

            for _ in range(1, depth - 1):
                self.layers.append(spectral_norm(nn.Linear(D_h, D_h)))
                self.layers.append(nn.ReLU())
            self.layers.append(spectral_norm(nn.Linear(D_h, D_out)))

    def forward(self, x):
        for layer in self.layers:
            x = layer(x)
        return x

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
        data = np.array([msg.rol, msg.pit, msg.yaw, msg.drol, msg.dpit, msg.dyaw, msg.xa, msg.ya, msg.za, 0, msg.ul, msg.beta, msg.Thr_out])
        sample_tensor = torch.tensor(data,requires_grad=True,dtype=torch.float).to(self.device).unsqueeze(0).view(1,-1)
        prediction = self.predictor(sample_tensor)
        # gradient = torch.autograd.grad(prediction,sample_tensor,grad_outputs=torch.ones_like(prediction),create_graph=True)[0]
        result=prediction.detach().cpu().numpy()[0]
        u=msg.Thr_out
        diff=0.05
        rate=0.5
        if abs(msg.desired_dpit-result)<diff:
            while abs(msg.desired_dpit-result)>0.3*diff:
                ulast = u
                u=rate*(msg.desired_dpit-result)
                if abs(ulast-u)<0.001:
                    break
                # print(u)
                data[-1]=u
                sample_tensor = torch.tensor(data,dtype=torch.float).to(self.device).unsqueeze(0).view(1,-1)
                prediction = self.predictor(sample_tensor)
                result=prediction.detach().cpu().numpy()[0]
                if abs(msg.desired_dpit-result)>diff:
                    print("FAILED Use PID")
                    self.new_traj.u_thr=u
                    if self.new_traj.rc_state==2:
                        self.new_traj.rc_state=1
                    self.message_publisher.publish(self.new_traj)
                    return
            print("Success")
            self.new_traj.u_thr=u
            self.message_publisher.publish(self.new_traj)
            return
        else:
            desired_pitch=sign(msg.desired_dpit-result)*diff+msg.dpit
            while abs(desired_pitch-result)>diff:
                ulast = u
                u=rate*(desired_pitch-result)
                if abs(ulast-u)<0.001:
                    break
                # print(u)
                data[-1]=u
                sample_tensor = torch.tensor(data,dtype=torch.float).to(self.device).unsqueeze(0).view(1,-1)
                prediction = self.predictor(sample_tensor)
                result=prediction.detach().cpu().numpy()[0]
                if abs(desired_pitch-result)>diff:
                    print("FAILED Use PID")
                    self.new_traj.u_thr=u
                    if self.new_traj.rc_state==2:
                        self.new_traj.rc_state=1
                    self.message_publisher.publish(self.new_traj)
                    return
            print("Success")
            self.new_traj.u_thr=u
            self.message_publisher.publish(self.new_traj)
            return

    def traj_cb(self,msg):
        self.new_traj=msg


if __name__ == '__main__':
    depth=3
    feature_num = 13
    output_dim = 1
    batchsize = 1
    # if torch.cuda.is_available():
    #     print("CUDA is available!")
    #     print("Number of GPUs:", torch.cuda.device_count())
    #     print("CUDA Device Name:", torch.cuda.get_device_name(0))
    #     print("CUDA Device Capability:", torch.cuda.get_device_capability(0))
    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    model = Net(depth=depth, D_in=feature_num, D_h=256, D_out=output_dim).to(device)
    model_path = '/home/xxh/Doublebee/checkpoint/3/best_model_weights.pth'
    model.load_state_dict(torch.load(model_path, map_location='cuda:0'))
    import rospy
    rospy.init_node("seg_node")
    yolox_ros = SegRos(predictor=model,device=device)
    rospy.spin()
