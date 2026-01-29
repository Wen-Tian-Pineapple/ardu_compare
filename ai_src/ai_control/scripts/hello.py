#! /usr/bin/env python
import numpy as np
import os
import pycuda.driver as cuda
import numpy as np
import torch
import torch.nn as nn
from torch.nn.utils import spectral_norm
from ai_control.msg import JaiRaw,Result
import tensorrt as trt

def load_engine(engine_file_path):
    assert os.path.exists(engine_file_path)
    print("Reading engine from file {}".format(engine_file_path))
    with open(engine_file_path, "rb") as f, trt.Runtime(TRT_LOGGER) as runtime:
        return runtime.deserialize_cuda_engine(f.read())

def infer(engine, img):
    input_image = img
    with engine.create_execution_context() as context:
        ctx = cuda.Context.attach()
        context.set_binding_shape(engine.get_binding_index("input"), (1,600))
        bindings = []

        for binding in engine:
            binding_idx = engine.get_binding_index(binding)
            size = trt.volume(context.get_binding_shape(binding_idx))
            dtype = trt.nptype(engine.get_binding_dtype(binding))

            if engine.binding_is_input(binding):
                input_buffer = np.ascontiguousarray(input_image)
                input_memory = cuda.mem_alloc(input_buffer.nbytes)
                bindings.append(int(input_memory))
                cuda.memcpy_htod(input_memory, input_buffer)

            else:
                output_buffer = np.empty(size, dtype)
                output_memory = cuda.mem_alloc(output_buffer.nbytes)
                bindings.append(int(output_memory))

        stream = cuda.Stream()

        context.execute_async_v2(bindings=bindings, stream_handle=stream.handle)
        cuda.memcpy_dtoh_async(output_buffer, output_memory, stream)
        stream.synchronize()
        ctx.pop()
        # ctx.detach()

        # Release GPU memory
        input_memory.free()
        output_memory.free()
        # Return the output as needed
        return output_buffer.copy()

class SegRos(object):
    def __init__(self, predictor):
        self.predictor = predictor
        self.buffer_size = 40
        self.message_buffer = []
        self.message_subscriber = rospy.Subscriber('/mavros/jai_raw', JaiRaw, callback=self.message_callback, queue_size=1)
        self.message_publisher = rospy.Publisher('/gradient_result', Result, queue_size=1)

    def message_callback(self, msg):
        data = np.array([msg.pit, msg.yaw, msg.drol, msg.dpit, msg.dyaw, msg.ddrol, msg.ddpit, msg.ddyaw, msg.desired_dpitch, msg.PWM1/2000, msg.PWM2/2000, msg.PWM3/2000, msg.PWM4/2000, msg.PWM5/2000, msg.PWM6/2000])

        self.message_buffer.append(data)
        if len(self.message_buffer) == self.buffer_size:
            sample = np.stack(self.message_buffer, axis=0)
            sample = sample.astype(np.float32)
            sample = np.expand_dims(sample, axis=0)
            sample = sample.reshape(1, -1)
            prediction = infer(self.predictor,sample)
            print(prediction,msg.rol)
            published_msg = Result()
            published_msg.result = prediction
            self.message_publisher.publish(published_msg)
            self.message_buffer.pop(0)

if __name__ == '__main__':

    TRT_LOGGER = trt.Logger()
    model_path = '/home/Disk/xxh/result/onnx/rol/split/6_layer/bset_model.engine'
    model = load_engine(model_path)
    import rospy
    rospy.init_node("seg_node")
    yolox_ros = SegRos(predictor=model)
    rospy.spin()
