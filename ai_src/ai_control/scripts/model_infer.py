#! /usr/bin/env python

import numpy as np
import torch
import torch.nn as nn
from torch.nn.utils import spectral_norm
from ai_control.msg import JaiRaw,Result



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



class SegRos(object):
    def __init__(self, predictor, device):
        self.predictor = predictor
        self.device = device
        self.message_buffer = []
        self.message_subscriber = rospy.Subscriber('/mavros/jai_raw', JaiRaw, callback=self.message_callback, queue_size=1)
        self.message_publisher = rospy.Publisher('/gradient_result', Result, queue_size=1)

    def message_callback(self, msg):
        # print(msg)
        data = np.array([msg.rol, msg.pit, msg.yaw, msg.drol, msg.dpit, msg.dyaw, msg.xa, msg.ya, msg.za, msg.ur, msg.ul, msg.beta, msg.Thr_out])
        sample_tensor = torch.tensor(data,dtype=torch.float).to(self.device).unsqueeze(0).view(1,-1)
        prediction = self.predictor(sample_tensor)
        print(prediction,msg.dpit)
        published_msg = Result()
        published_msg.result = prediction.detach().cpu().numpy()[0]
        self.message_publisher.publish(published_msg)

if __name__ == '__main__':
    depth=3
    feature_num = 13
    output_dim = 1
    batchsize = 1
    device = torch.device('cuda:0' if torch.cuda.is_available() else 'cpu')
    model = Net(depth=depth, D_in=feature_num, D_h=256, D_out=output_dim).to(device)
    model_path = '/home/Disk/xxh/result_new/split/3_layer/best_model_weights.pth'
    model.load_state_dict(torch.load(model_path))
    import rospy
    rospy.init_node("seg_node")
    yolox_ros = SegRos(predictor=model,device=device)
    rospy.spin()
