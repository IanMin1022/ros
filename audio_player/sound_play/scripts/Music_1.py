#!/usr/bin/env python

import sys
import rospy
from std_msgs.msg import String
from sound_play.msg import SoundRequest
from sound_play.libsoundplay import SoundClient

def callback(data):
    #rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)
    flag = data.data
    soundhandle = SoundClient()
    if flag == "50":
        soundhandle.playWave("Amnesia.mp3", 1)

def listener():
    rospy.init_node('Music_1', anonymous = True)
    rospy.Subscriber('on_air', String, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
