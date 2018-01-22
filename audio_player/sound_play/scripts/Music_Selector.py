#!/usr/bin/env python

import sys
import rospy
from std_msgs.msg import UInt32
from sound_play.msg import SoundRequest
from sound_play.libsoundplay import SoundClient

def callback(data):
    #rospy.loginfo(rospy.get_caller_id() + 'I heard %s', data.data)
    flag = data.data
    soundhandle = SoundClient()
    if flag == 0:
        title = rospy.get_param('~song_title', '1sec.mp3')
        soundhandle.playWave(title, 1)

def listener():
    rospy.init_node('Music_Selector')
    rospy.Subscriber('/current_time', UInt32, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()
