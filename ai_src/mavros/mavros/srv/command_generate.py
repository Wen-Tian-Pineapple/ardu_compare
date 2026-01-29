#!/usr/bin/env python

import rospy
from std_msgs.msg import Header
from mavros_msgs.msg import JAIOut
import sys
import select
import termios
import tty

def angle_time_func(t,exptype,static_angle,dynamic_max):
    if exptype==1:
        return int((500*static_angle/90)+500)
    elif exptype==2:
        if t<2:
            return int((500*static_angle/90)+500)
        elif t>=2 and t<6:
            angle_desired=((dynamic_max-static_angle)*(t-2)/4)+static_angle
            return int((500*angle_desired/90)+500)
        elif t>=6 and t<8:
            return int((500*dynamic_max/90)+500)
        elif t>=8 and t<10:
            angle_desired=dynamic_max-(dynamic_max-static_angle)*(t-8)/2
            return int((500*angle_desired/90)+500)
        else:
            return int((500*static_angle/90)+500)
    else:
        return 1000
    
def time_wheel_curve(t,low,high):
    if t<5:
        return low
    elif t>=5 and t<6:
        return (t-5)*(high-low)+low
    elif t>=6 and t<=7:
        return high
    elif t>=7 and t<8:
        return high*(8-t)
    else:
        return 0

def wheel_time_func(t,envclass,wheelstate,steep_hold,max_wheel):
    if wheelstate==1:
        if envclass==1:
            return -steep_hold
        elif envclass==2:
            return 0
        else:
            return 0
    elif wheelstate==2:
        if envclass==1:
            return -time_wheel_curve(t,steep_hold,max_wheel)
        elif envclass==2:
            return -time_wheel_curve(t,0,max_wheel)
        else:
            return 0

    else:
        return 0


def main():
    rospy.init_node('jai_publisher')
    # pub = rospy.Publisher('/Jai_command', JAIOut, queue_size=10)
    pub = rospy.Publisher('/Jai_traj', JAIOut, queue_size=10)


    Begin_task=False
    Frame=1   #1:PID 2:NN
    Exptype=2 #1:Static 2:Dynamics
    envclass=1 #1:steep 2:Plane
    steep_hold=0.10 #steep_hold abs
    wheelstate=2#1:static 2:Dynamics
    max_wheel=0.30

    static_angle_deg=90
    dynamic_angle_range_deg=45

    print("Press Enter to start...")
    while not rospy.is_shutdown():
        while not Begin_task:
            if sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
                print("Press finished 1")
                Begin_task = True
                termios.tcflush(sys.stdin, termios.TCIOFLUSH)
        print("Begin Task")
        time_start=rospy.Time.now().to_sec()
        rate = rospy.Rate(100)
        while rospy.Time.now().to_sec()-time_start<10:
            msg=JAIOut()
            h=Header()
            h.stamp=rospy.Time.now()
            msg.header=h
            time_current=rospy.Time.now().to_sec()-time_start
            if time_current<2:
                msg.rc_state=1
            else:
                msg.rc_state=Frame
            msg.u_thr=0       
            msg.pit_pwm=angle_time_func(time_current,Exptype,static_angle_deg,dynamic_angle_range_deg)     
            msg.wh_r=0
            msg.wh_l=-wheel_time_func(time_current,envclass,wheelstate,steep_hold,max_wheel)
            pub.publish(msg)
            rate.sleep()
        msg=JAIOut()
        h=Header()
        h.stamp=rospy.Time.now()
        msg.header=h
        time_current=rospy.Time.now().to_sec()-time_start
        msg.rc_state=0
        msg.u_thr=0       
        msg.pit_pwm=angle_time_func(time_current,Exptype,static_angle_deg,dynamic_angle_range_deg)     
        msg.wh_r=0
        msg.wh_l=-wheel_time_func(time_current,envclass,wheelstate,steep_hold,max_wheel)
        pub.publish(msg)
        break
    print("Finish all task")




if __name__ == '__main__':

    main()