#! /usr/bin/env python

import numpy as np
import torch
import torch.nn as nn
from torch.nn.utils import spectral_norm
from mavros_msgs.msg import JAIOut
from mavros_msgs.msg import JaiRaw


if __name__ == '__main__':
    depth=3
    feature_num = 13
    output_dim = 1
    batchsize = 1

    device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
    model = Net(depth=depth, D_in=feature_num, D_h=256, D_out=output_dim).to(device)
    model_path = '/home/xxh/Doublebee/checkpoint/3/best_model_weights.pth'
    model.load_state_dict(torch.load(model_path, map_location='cuda:0'))
    import rospy
    rospy.init_node("seg_node")
    yolox_ros = SegRos(predictor=model,device=device)
    rospy.spin()