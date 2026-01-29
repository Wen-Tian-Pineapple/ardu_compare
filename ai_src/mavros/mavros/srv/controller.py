#!/usr/bin/env python

import rospy
from std_msgs.msg import Header
from mavros_msgs.msg import JAIOut
import sys
import select
import termios
import tty

def create_message():
    msg = JAIOut()
    msg.header = Header()
    msg.rc_state = 1  # Example value, set as needed
    msg.pit_pwm = 200  # Example value, set as needed
    msg.wh_r = 1.0  # Example value, set as needed
    msg.wh_l = 1.0  # Example value, set as needed
    msg.u_thr = 0.2  # Example value, set as needed
    return msg

def get_key():
    tty.setraw(sys.stdin.fileno())
    key = sys.stdin.read(1)
    termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attr)
    return key

def main():
    rospy.init_node('jai_publisher')
    pub = rospy.Publisher('/Jai_command', JAIOut, queue_size=10)
    rate = rospy.Rate(10)  # 10 Hz

    print("Press Enter to publish a message and 's' to stop the node.")

    while not rospy.is_shutdown():
        if sys.stdin in select.select([sys.stdin], [], [], 0)[0]:
            key = get_key()
            if key == 'b':  # Enter key
                msg = create_message()
                msg.header.stamp = rospy.Time.now()
                pub.publish(msg)
                rospy.loginfo("Published message: %s", msg)
            elif key == 's':
                rospy.loginfo("Stopping the node.")
                break
        rate.sleep()

if __name__ == '__main__':
    old_attr = termios.tcgetattr(sys.stdin)
    try:
        main()
    except rospy.ROSInterruptException:
        pass
    finally:
        termios.tcsetattr(sys.stdin, termios.TCSADRAIN, old_attr)
