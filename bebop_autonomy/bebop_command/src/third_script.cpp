#include "ros/ros.h"
#include "Control.h"
#include <std_msgs/Empty.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Script_publisher.h"

/******************************************Command***********************************************
    NAME          |     TIME     |     DESCRIPTION
-------------------------------------------------------------------------------------------------
  TAKE_OFF        |   3000(ms)   |
  LAND            |   3000(ms)   |
  FLIP_FORWARD    |   1000(ms)   |
  FLIP_BACKWARD   |   1000(ms)   |
  FLIP_LEFT       |   1000(ms)   |
  FLIP_RIGHT      |   1000(ms)   |
  UPDOWN_GREET    |    250(ms)   |    tilt to forward
  UPDOWN_x        |  800*x(ms)   |    tilt to forward and backward (e.g. UPDOWN_1, UPDOWN_2, max 8)
  SIDE_LEFT       |    300(ms)   |    tilt once to left
  SIDE_RIGHT      |    300(ms)   |    tilt once to right
  SIDE_x          |  800*x(ms)   |    tilt to side (e.g. SIDE_1, SIDE_2, max 8)

  *****   -180 < yaw < 180    :  0  is ahead to forward   *******
************************************************************************************************/

void write_scrip_here(void) {
  /* Take Off */
      script->script_1("TAKE_OFF");
      script->script_2("TAKE_OFF");
      script->script_3("TAKE_OFF");
      script->script_4("TAKE_OFF");
      script->script_5("TAKE_OFF");
      script->script_6("TAKE_OFF");
      script->script_7("TAKE_OFF");
      script->timer(3);

    /* Satrt_Hovering */
      script->script_1("3 0.5 2 0");
      script->script_2("1 0.5 2 0");
      script->script_3("-1 0.5 2 0");
      script->script_4("-3 0.5 2 0");
      script->script_5("2 -2.5 2 0");
      script->script_6("0 -2.5 2 0");
      script->script_7("-2 -2.5 2 0");
      script->timer(8.0);

    /* Moving */
      script->script_1("0 2.5 1.5 0");
      script->script_2("-2.331438 1.887961 1.5 0");
      script->script_3("-2.934443 -0.623735 2.1 0");
      script->script_4("-1.361971 -2.67302 1.5 0");
      script->script_5("1.22021 -2.740636 1.5 0");
      script->script_6("2.897777 -0.776457 2.1 0");
      script->script_7("2.427051 1.763356 1.5 0");
      script->timer(9.0);

    /* Making the Circle */
      script->script_1("0 2.5 1.5 0");
      script->script_2("-1.942865 1.573301 1.5 0");
      script->script_3("-2.445369 -0.519779 1.5 0");
      script->script_4("-1.134976 -2.227516 1.5 0");
      script->script_5("1.016842 -2.283864 1.5 0");
      script->script_6("2.414815 -0.647048 1.5 0");
      script->script_7("2.022542 1.469463 1.5 0");
      script->timer(10.0);

      script->script_1("0 2.5 1.5 0");
      script->script_2("-1.942865 1.573301 1.5 0");
      script->script_3("-2.445369 -0.519779 1.5 0");
      script->script_4("-1.134976 -2.227516 1.5 0");
      script->script_5("0.016842 -2.283864 1.5 0");
      script->script_6("2.414815 -0.647048 1.5 0");
      script->script_7("2.022542 1.469463 1.5 0");
      script->timer(11.0);

      script->script_1("-0.855050 2.349232 1.5 0");
      script->script_2("-2.363796 0.81392 1.5 0");
      script->script_3("-2.120120 -1.324798 1.5 0");
      script->script_4("-0.304673 -2.481365 1.5 0");
      script->script_5("1.736646 -1.79835 1.5 0");
      script->script_6("2.490487 0.217889 1.5 0");
      script->script_7("1.397982 2.072594 1.5 0");
      script->timer(12.0);

      script->script_1("-1.606969 1.915111 1.5 0");
      script->script_2("-2.499619 -0.043631 1.5 0");
      script->script_3("-1.539154 -1.970027 1.5 0");
      script->script_4("0.562378 -2.435925 1.5 0");
      script->script_5("2.246985 -1.095928 1.5 0");
      script->script_6("2.265769 1.056546 1.5 0");
      script->script_7("0.604805 2.425739 1.5 0");
      script->timer(13.0);

      script->script_1("-2.165064 1.25 1.5 0");
      script->script_2("-2.333951 -0.89592 1.5 0");
      script->script_3("-0.772542 -2.377641 1.5 0");
      script->script_4("1.361598 -2.096676 1.5 0");
      script->script_5("2.486305 -0.261321 1.5 0");
      script->script_6("1.767767 1.767767 1.5 0");
      script->script_7("-0.261321 2.486305 1.5 0");
      script->timer(14.0);

      script->script_1("-2.462019 0.43412 1.5 0");
      script->script_2("-1.886774 -1.640148 1.5 0");
      script->script_3("0.087249 -2.498477 1.5 0");
      script->script_4("1.996589 -1.504538 1.5 0");
      script->script_5("2.425739 0.604805 1.5 0");
      script->script_6("1.056546 2.265769 1.5 0");
      script->script_7("-1.095928 2.246985 1.5 0");
      script->timer(15.0);

      script->script_1("-2.462019 -0.43412 1.5 0");
      script->script_2("-1.212024 -2.186549 1.5 0");
      script->script_3("0.936516 -2.317960 1.5 0");
      script->script_4("2.390762 -0.730929 1.5 0");
      script->script_5("2.072594 1.397982 1.5 0");
      script->script_6("0.217889 2.490487 1.5 0");
      script->script_7("-1.798350 1.736646 1.5 0");
      script->timer(16.0);

      script->script_1("-2.165064 -1.25 1.5 0");
      script->script_2("-0.391086 -2.469221 1.5 0");
      script->script_3("1.672827 -1.857862 1.5 0");
      script->script_4("2.496574 0.13084 1.5 0");
      script->script_5("1.469463 2.022542 1.5 0");
      script->script_6("-0.647048 2.414815 1.5 0");
      script->script_7("-2.283864 1.016842 1.5 0");
      script->timer(17.0);

      script->script_1("-1.606969 -1.915111 2.0 0");
      script->script_2("0.477022 -2.454068 2.0 0");
      script->script_3("2.207369 -1.173679 2.0 0");
      script->script_4("2.301262 0.976828 2.0 0");
      script->script_5("0.689093 2.403154 2.0 0");
      script->script_6("-1.433941 2.04788 2.0 0");
      script->script_7("-2.493910 0.174391 2.0 0");
      script->timer(18.0);

      script->script_1("-0.85505 -2.349232 2.0 0");
      script->script_2("1.287595 -2.142918 2.0 0");
      script->script_3("2.47567 -0.347933 2.0 0");
      script->script_4("1.828384 1.704996 2.0 0");
      script->script_5("-0.174391 2.49391 2.0 0");
      script->script_6("-2.047880 1.433941 2.0 0");
      script->script_7("-2.403154 -0.689093 2.0 0");
      script->timer(19.0);

      script->script_1("0 -2.5 1.5 0");
      script->script_2("1.942865 -1.573301 2.0 0");
      script->script_3("2.445369 0.519779 2.0 0");
      script->script_4("1.134976 2.227516 2.0 0");
      script->script_5("-1.016842 2.283864 2.0 0");
      script->script_6("-2.414815 0.647048 2.0 0");
      script->script_7("-2.022542 -1.469463 2.0 0");
      script->timer(20.0);

      script->script_1("0.85505 -2.349232 2.0 0");
      script->script_2("2.363796 -0.81392 2.0 0");
      script->script_3("2.12012 1.324798 2.0 0");
      script->script_4("0.304673 2.481365 2.0 0");
      script->script_5("-1.736646 1.79835 2.0 0");
      script->script_6("-2.490487 -0.217889 2.0 0");
      script->script_7("-1.397982 -2.072594 2.0 0");
      script->timer(21.0);

      script->script_1("1.606969 -1.915111 2.0 0");
      script->script_2("2.499619 0.043631 2.0 0");
      script->script_3("1.539154 1.970027 2.0 0");
      script->script_4("-0.562378 2.435925 2.0 0");
      script->script_5("-2.246985 1.095928 2.0 0");
      script->script_6("-2.265769 -1.056546 2.0 0");
      script->script_7("-0.604805 -2.425739 2.0 0");
      script->timer(22.0);

      script->script_1("2.165064 -1.25 1.5 0");
      script->script_2("2.333951 0.89592 2.0 0");
      script->script_3("0.772542 2.377641 2.0 0");
      script->script_4("-1.361598 2.096676 2.0 0");
      script->script_5("-2.486305 0.261321 2.0 0");
      script->script_6("-1.767767 -1.767767 2.0 0");
      script->script_7("0.261321 -2.486305 2.0 0");
      script->timer(23.0);

      script->script_1("2.462019 -0.43412 1.5 0");
      script->script_2("1.886774 1.640148 2.0 0");
      script->script_3("-0.087249 2.498477 2.0 0");
      script->script_4("-1.996589 1.504538 2.0 0");
      script->script_5("-2.425739 -0.604805 2.0 0");
      script->script_6("-1.056546 -2.265769 2.0 0");
      script->script_7("1.095928 -2.246985 1.5 0");
      script->timer(24.0);

      script->script_1("2.462019 0.43412 1.5 0");
      script->script_2("1.212024 2.186549 2.0 0");
      script->script_3("-0.936516 2.31796 2.0 0");
      script->script_4("-2.390762 0.730929 2.0 0");
      script->script_5("-2.072594 -1.397982 2.0 0");
      script->script_6("-0.217889 -2.490487 1.5 0");
      script->script_7("1.79835 -1.736646 1.5 0");
      script->timer(25.0);

      script->script_1("2.165064 1.25 1.5 0");
      script->script_2("0.391086 2.469221 2.0 0");
      script->script_3("-1.672827 1.857862 2.0 0");
      script->script_4("-2.496574 -0.13084 2.0 0");
      script->script_5("-1.469463 -2.022542 1.5 0");
      script->script_6("0.647048 -2.414815 1.5 0");
      script->script_7("2.283864 -1.016842 1.5 0");
      script->timer(26.0);

      script->script_1("1.606969 1.915111 1.5 0");
      script->script_2("-0.477022 2.454068 2.0 0");
      script->script_3("-2.207369 1.173679 2.0 0");
      script->script_4("-2.301262 -0.976828 1.5 0");
      script->script_5("-0.689093 -2.403154 1.5 0");
      script->script_6("1.433941 -2.04788 1.5 0");
      script->script_7("2.49391 -0.174391 1.5 0");
      script->timer(27.0);

      script->script_1("0.85505 2.349232 1.5 0");
      script->script_2("-1.287595 2.142918 2.0 0");
      script->script_3("-2.47567 0.347933 1.5 0");
      script->script_4("-1.828384 -1.704996 1.5 0");
      script->script_5("0.174391 -2.49391 1.5 0");
      script->script_6("2.04788 -1.433941 1.5 0");
      script->script_7("2.403154 0.689093 1.5 0");
      script->timer(28.0);

      script->script_1("0 2.5 1.5 0");
      script->script_2("-1.942865 1.573301 1.5 0");
      script->script_3("-2.445369 -0.519779 1.5 0");
      script->script_4("-1.134976 -2.227516 1.5 0");
      script->script_5("1.016842 -2.283864 1.5 0");
      script->script_6("2.414815 -0.647048 1.5 0");
      script->script_7("2.022542 1.469462 1.5 0");
      script->timer(29.0);

      script->script_1("-0.85505 2.349232 1.7 0");
      script->script_2("-2.363796 0.81392 2.0 0");
      script->script_3("-2.120120 -1.324798 1.7 0");
      script->script_4("-0.304673 -2.481365 2.0 0");
      script->script_5("1.736646 -1.79835 1.7 0");
      script->script_6("2.490487 0.217889 2.0 0");
      script->script_7("1.397982 2.072594 1.7 0");
      script->timer(30.0);

      script->script_1("-1.606969 1.915111 1.7 0");
      script->script_2("-2.499619 -0.043631 1.7 0");
      script->script_3("-1.539154 -1.970027 1.7 0");
      script->script_4("0.562378 -2.435925 1.7 0");
      script->script_5("2.246985 -1.095928 1.7 0");
      script->script_6("2.265769 1.056546 1.7 0");
      script->script_7("0.604805 2.425739 1.7 0");
      script->timer(31.0);

      script->script_1("-2.165064 1.25 2.0 0");
      script->script_2("-2.333951 -0.89592 1.7 0");
      script->script_3("-0.772542 -2.377641 2.0 0");
      script->script_4("1.361598 -2.096676 1.7 0");
      script->script_5("2.486305 -0.261321 2.0 0");
      script->script_6("1.767767 1.767767 1.7 0");
      script->script_7("-0.261321 2.486305 2.0 0");
      script->timer(32.0);

      script->script_1("-2.462019 0.56588 1.7 0");
      script->script_2("-1.886774 -1.640148 2.0 0");
      script->script_3("0.087249 -2.498477 1.7 0");
      script->script_4("1.996589 -1.504538 2.0 0");
      script->script_5("2.425739 1.604805 1.7 0");
      script->script_6("1.056546 2.265769 2.0 0");
      script->script_7("-1.095928 2.246985 1.7 0");
      script->timer(33.0);

      script->script_1("-2.462019 -0.43412 2.0 0");
      script->script_2("-1.212024 -2.186549 1.7 0");
      script->script_3("0.936516 -2.31796 2.0 0");
      script->script_4("2.390762 -0.7309291 1.7 0");
      script->script_5("2.072594 1.397982 2.0 0");
      script->script_6("0.217889 2.490487 1.7 0");
      script->script_7("-1.79835 1.736646 2.0 0");
      script->timer(34.0);

      script->script_1("-2.165064 -1.25 1.7 0");
      script->script_2("-0.391086 -2.469221 2.0 0");
      script->script_3("1.672827 -1.857862 1.7 0");
      script->script_4("2.496574 0.13084 2.0 0");
      script->script_5("1.469463 2.022542 1.7 0");
      script->script_6("-0.647048 2.414815 2.0 0");
      script->script_7("-2.283864 1.016842 1.7 0");
      script->timer(35.0);

      script->script_1("-1.606969 -1.915111 2.0 0");
      script->script_2("0.477022 -2.454068 1.7 0");
      script->script_3("2.207369 -1.173679 2.0 0");
      script->script_4("2.301262 0.976828 1.7 0");
      script->script_5("0.689093 2.403154 2.0 0");
      script->script_6("-1.433941 2.04788 1.7 0");
      script->script_7("-2.49391 0.174391 2.0 0");
      script->timer(36.0);

      script->script_1("-0.85505 -2.349232 1.7 0");
      script->script_2("1.287595 -2.142918 2.0 0");
      script->script_3("2.47567 -0.347933 1.7 0");
      script->script_4("1.828384 1.704996 2.0 0");
      script->script_5("-0.174391 2.49391 1.7 0");
      script->script_6("-2.047880 1.433941 2.0 0");
      script->script_7("-2.403154 -0.689093 1.7 0");
      script->timer(37.0);

      script->script_1("0 -2.5 1.5 0");
      script->script_2("1.942865 -1.573301 1.5 0");
      script->script_3("2.445369 0.519779 1.5 0");
      script->script_4("1.134976 2.227516 1.5 0");
      script->script_5("-1.016842 2.283864 1.5 0");
      script->script_6("-2.414815 0.647048 1.5 0");
      script->script_7("-2.022542 -1.469463 1.5 0");
      script->timer(38.0);

      script->script_1("0.85505 -2.349232 1.5 0");
      script->script_2("2.363796 -0.813920 1.5 0");
      script->script_3("2.12012 1.324798 1.5 0");
      script->script_4("0.304673 2.518635 2.0 0");
      script->script_5("-1.736646 1.79835 1.5 0");
      script->script_6("-2.490487 -0.217889 1.5 0");
      script->script_7("-1.397982 -2.072594 1.5 0");
      script->timer(39.0);

      script->script_1("1.606969 -1.915111 1.5 0");
      script->script_2("2.499619 0.043631 1.5 0");
      script->script_3("1.539154 1.970027 2.0 0");
      script->script_4("-0.562378 2.435925 2.0 0");
      script->script_5("-2.246985 1.095928 1.5 0");
      script->script_6("-2.265769 -1.056546 1.5 0");
      script->script_7("-0.604805 -2.425739 1.5 0");
      script->timer(40.0);

      script->script_1("2.165064 -1.25 1.5 0");
      script->script_2("2.333951 0.89592 2.0 0");
      script->script_3("0.772542 2.377641 2.0 0");
      script->script_4("-1.361598 2.096676 2.0 0");
      script->script_5("-2.486305 0.261321 1.5 0");
      script->script_6("-1.767767 -1.767767 1.5 0");
      script->script_7("0.261321 -2.486305 1.5 0");
      script->timer(41.0);

      script->script_1("2.462019 -0.434120 2.0 0");
      script->script_2("1.886774 1.640148 2.0 0");
      script->script_3("-0.087249 2.498477 2.0 0");
      script->script_4("-1.996589 1.504538 2.0 0");
      script->script_5("-2.425739 -0.604805 1.5 0");
      script->script_6("-1.056546 -2.265769 1.5 0");
      script->script_7("1.095928 -2.246985 1.5 0");
      script->timer(42.0);

      script->script_1("2.462019 0.43412 2.0 0");
      script->script_2("1.212024 2.186549 2.0 0");
      script->script_3("-0.936516 2.31796 2.0 0");
      script->script_4("-2.390762 1.730929 2.0 0");
      script->script_5("-2.072594 -1.3979825 1.5 0");
      script->script_6("-0.217889 -2.490487 1.5 0");
      script->script_7("1.79835 -1.736646 2.0 0");
      script->timer(43.0);

      script->script_1("2.165064 1.25 2.0 0");
      script->script_2("0.391086 2.469221 2.0 0");
      script->script_3("-1.672827 1.857862 2.0 0");
      script->script_4("-2.496574 -0.130840 2.0 0");
      script->script_5("-1.469463 -2.022542 1.5 0");
      script->script_6("0.647048 -2.414815 2.0 0");
      script->script_7("2.283864 -1.016842 2.0 0");
      script->timer(44.0);

      script->script_1("1.606969 1.915111 2.0 0");
      script->script_2("-0.477022 2.454068 2.0 0");
      script->script_3("-2.207369 1.173679 2.0 0");
      script->script_4("-2.301262 -0.976828 2.0 0");
      script->script_5("-0.689093 -2.403154 2.0 0");
      script->script_6("1.433941 -2.047880 2.0 0");
      script->script_7("2.49391 -0.174391 2.0 0");
      script->timer(45.0);

      script->script_1("0.85505 2.349232 1.5 0");
      script->script_2("-1.287595 2.142918 1.5 0");
      script->script_3("-2.47567 0.347933 1.5 0");
      script->script_4("-1.828384 -1.704996 1.5 0");
      script->script_5("0.174391 -2.49391 1.5 0");
      script->script_6("2.04788 -1.433941 1.5 0");
      script->script_7("2.403154 0.689093 1.5 0");
      script->timer(46.0);

      script->script_1("0. 2.5 1.5 0");
      script->script_2("-1.942865 1.573301 1.5 0");
      script->script_3("-2.445369 -0.519779 1.5 0");
      script->script_4("-1.134976 -2.227516 1.5 0");
      script->script_5("1.016842 -2.283864 1.5 0");
      script->script_6("2.414815 -0.647048 1.5 0");
      script->script_7("2.022542 1.469463 1.5 0");
      script->timer(47.0);

      /* Flip */
      script->script_1("0 2.5 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("2 2 1.5 0");
      script->timer(48.0);

      script->script_1("0 0.5 1.5 0");
      script->script_2("FLIP_LEFT");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("FLIP_RIGHT");
      script->timer(49.0);

      script->script_1("0 -1 1.5 0");
      script->script_2("-3 2 1.5 0");
      script->script_3("-3 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("3 0 1.5 0");
      script->script_7("3 2 1.5 0");
      script->timer(50.0);

      script->script_1("0 -2.5 1.5 0");
      script->script_2("-3 2 1.5 0");
      script->script_3("-3 0 1.5 0");
      script->script_4("-3 -2 1.5 0");
      script->script_5("3 -2 1.5 0");
      script->script_6("3 0 1.5 0");
      script->script_7("3 2 1.5 0");
      script->timer(51.0);

      script->script_1("0 -2.5 1.5 0");
      script->script_2("-3 2 1.5 0");
      script->script_3("-3 0 1.5 0");
      script->script_4("-3 -2 1.5 0");
      script->script_5("3 -2 1.5 0");
      script->script_6("3 0 1.5 0");
      script->script_7("3 2 1.5 0");
      script->timer(53.0);

      script->script_1("0 -0.5 1.5 0");
      script->script_2("-3.5 2 1.5 0");
      script->script_3("-3.5 0 1.5 0");
      script->script_4("-3.5 -2 1.5 0");
      script->script_5("3.5 -2 1.5 0");
      script->script_6("3.5 0 1.5 0");
      script->script_7("3.5 2 1.5 0");
      script->timer(55.0);

      script->script_1("0 0.5 1.5 0");
      script->script_2("-3 2 1.5 0");
      script->script_3("-3 0 1.5 0");
      script->script_4("FLIP_RIGHT");
      script->script_5("FLIP_LEFT");
      script->script_6("3 0 1.5 0");
      script->script_7("3 2 1.5 0");
      script->timer(56.0);

      script->script_1("0 1.5 1.5 0");
      script->script_2("-3 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("3 2 1.5 0");
      script->timer(57.0);

      script->script_1("0 2.5 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("2 2 1.5 0");
      script->timer(60.0);

      script->script_1("0 2.5 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("2 2 1.5 0");
      script->timer(61.0);

      script->script_1("0 0 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("2 2 1.5 0");
      script->timer(62.0);

      script->script_1("1 0 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("FLIP_RIGHT");
      script->script_7("FLIP_RIGHT");
      script->timer(63.0);

      script->script_1("-1 0 1.5 0");
      script->script_2("FLIP_LEFT");
      script->script_3("FLIP_LEFT");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("2 2 1.5 0");
      script->timer(64.0);

      script->script_1("0 0 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("2 2 1.5 0");
      script->timer(66.0);

      script->script_1("0 2.5 1.5 0");
      script->script_2("-2 2.5 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -3 1.5 0");
      script->script_6("2 -1 1.5 0");
      script->script_7("2 1 1.5 0");
      script->timer(67.0);

      script->script_1("3 2.5 1.5 0");
      script->script_2("1 2.5 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -3 1.5 0");
      script->script_6("2 -1 1.5 0");
      script->script_7("2 1 1.5 0");
      script->timer(68.0);

      script->script_1("3 2.5 1.5 0");
      script->script_2("1 2.5 1.5 0");
      script->script_3("-1 2.5 1.5 0");
      script->script_4("-3 2.5 1.5 0");
      script->script_5("2 -3 1.5 0");
      script->script_6("2 -1 1.5 0");
      script->script_7("-3 -1 1.5 0");
      script->timer(69.0);

      script->script_1("3 2.5 1.5 0");
      script->script_2("1 2.5 1.5 0");
      script->script_3("-1 2.5 1.5 0");
      script->script_4("-3 2.5 1.5 0");
      script->script_5("3 -1 1.5 0");
      script->script_6("0 -1 1.5 0");
      script->script_7("-3 -1 1.5 0");
      script->timer(70.0);

      script->script_1("3 1 1.5 0");
      script->script_2("1 1 1.5 0");
      script->script_3("-1 1 1.5 0");
      script->script_4("-3 1 1.5 0");
      script->script_5("3 -1 1.5 0");
      script->script_6("0 -1 1.5 0");
      script->script_7("-3 -1 1.5 0");
      script->timer(72.0);

      script->script_1("3 1 1.7 0");
      script->script_2("1 1 2.1 0");
      script->script_3("-1 1 1.7 0");
      script->script_4("-3 1 1.3 0");
      script->script_5("3 -1 1.7 0");
      script->script_6("0 -1 2.04641 0");
      script->script_7("-3 -1 1.35359 0");
      script->timer(73.0);

      script->script_1("3 1 2.080423 0");
      script->script_2("1 1 1.823607 0");
      script->script_3("-1 1 1.319577 0");
      script->script_4("-3 1 1.576393 0");
      script->script_5("3 -1 2.080423 0");
      script->script_6("0 -1 1.616835 0");
      script->script_7("-3 -1 1.402742 0");
      script->timer(74.0);

      script->script_1("3 1 1.935114 0");
      script->script_2("1 1 1.376393 0");
      script->script_3("-1 1 1.464886 0");
      script->script_4("-3 1 2.023607 0");
      script->script_5("3 -1 1.935114 0");
      script->script_6("0 -1 1.302191 0");
      script->script_7("-3 -1 1.862695 0");
      script->timer(75.0);

      script->script_1("3 1 1.464886 0");
      script->script_2("1 1 1.376393 0");
      script->script_3("-1 1 1.935114 0");
      script->script_4("-3 1 2.023607 0");
      script->script_5("3 -1 1.464886 0");
      script->script_6("0 -1 1.537305 0");
      script->script_7("-3 -1 2.097809 0");
      script->timer(76.0);

      script->script_1("3 1 1.319577 0");
      script->script_2("1 1 1.823607 0");
      script->script_3("-1 1 2.080423 0");
      script->script_4("-3 1 1.576393 0");
      script->script_5("3 -1 1.319577 0");
      script->script_6("0 -1 1.997258 0");
      script->script_7("-3 -1 1.783165 0");
      script->timer(77.0);

      script->script_1("3 1 1.7 0");
      script->script_2("1 1 2.1 0");
      script->script_3("-1 1 1.7 0");
      script->script_4("-3 1 1.3 0");
      script->script_5("3 -1 1.7 0");
      script->script_6("0 -1 2.04641 0");
      script->script_7("-3 -1 1.35359 0");
      script->timer(78.0);

      script->script_1("3 1 2.080423 0");
      script->script_2("1 1 1.823607 0");
      script->script_3("-1 1 1.319577 0");
      script->script_4("-3 1 1.576393 0");
      script->script_5("3 -1 2.080423 0");
      script->script_6("0 -1 1.616835 0");
      script->script_7("-3 -1 1.402742 0");
      script->timer(79.0);

      script->script_1("3 1 1.935114 0");
      script->script_2("1 1 1.376393 0");
      script->script_3("-1 1 1.464886 0");
      script->script_4("-3 1 2.023607 0");
      script->script_5("3 -1 1.935114 0");
      script->script_6("0 -1 1.302191 0");
      script->script_7("-3 -1 1.862695 0");
      script->timer(80.0);

      script->script_1("3 1 1.464886 0");
      script->script_2("1 1 1.376393 0");
      script->script_3("-1 1 1.935114 0");
      script->script_4("-3 1 2.023607 0");
      script->script_5("3 -1 1.464886 0");
      script->script_6("0 -1 1.537305 0");
      script->script_7("-3 -1 2.097809 0");
      script->timer(81.0);

      script->script_1("3 1 1.319577 0");
      script->script_2("1 1 1.823607 0");
      script->script_3("-1 1 2.080423 0");
      script->script_4("-3 1 1.576393 0");
      script->script_5("3 -1 1.319577 0");
      script->script_6("0 -1 1.997258 0");
      script->script_7("-3 -1 1.783165 0");
      script->timer(82.0);

      script->script_1("3 1 1.7 0");
      script->script_2("1 1 2.1 0");
      script->script_3("-1 1 1.7 0");
      script->script_4("-3 1 1.3 0");
      script->script_5("3 -1 1.7 0");
      script->script_6("0 -1 2.04641 0");
      script->script_7("-3 -1 1.35359 0");
      script->timer(83.0);

      script->script_1("3 1 2.080423 0");
      script->script_2("1 1 1.823607 0");
      script->script_3("-1 1 1.319577 0");
      script->script_4("-3 1 1.576393 0");
      script->script_5("3 -1 2.080423 0");
      script->script_6("0 -1 1.616835 0");
      script->script_7("-3 -1 1.402742 0");
      script->timer(84.0);

      script->script_1("3 1 1.5 0");
      script->script_2("1 1 1.5 0");
      script->script_3("-1 1 1.5 0");
      script->script_4("-3 1 1.5 0");
      script->script_5("3 -1 1.5 0");
      script->script_6("0 -1 1.5 0");
      script->script_7("-3 -1 1.5 0");
      script->timer(86.0);

      script->script_1("3 1 1.5 0");
      script->script_2("2 1 2 0");
      script->script_3("-2 1 2 0");
      script->script_4("-3 1 1.5 0");
      script->script_5("3 -1 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -1 1.5 0");
      script->timer(88.0);

      script->script_1("2 -1 1.5 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-2 -1 1.5 0");
      script->script_5("3 -2.5 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -2.5 0");
      script->timer(89.0);

      script->script_1("2 -1 1.5 0");
      script->script_2("1 1 1.5 0");
      script->script_3("-1 1 1.5 0");
      script->script_4("-2 -1 1.5 0");
      script->script_5("3 -2.5 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -2.5 1.5 0");
      script->timer(90.0);

      script->script_1("UPDOWN_8");
      script->script_2("UPDOWN_8");
      script->script_3("UPDOWN_8");
      script->script_4("UPDOWN_8");
      script->script_5("UPDOWN_8");
      script->script_6("UPDOWN_8");
      script->script_7("UPDOWN_8");
      script->timer(96.0);

      script->script_1("2 -1 1.5 0");
      script->script_2("1 1 1.5 0");
      script->script_3("-1 1 1.5 0");
      script->script_4("-2 -1 1.5 0");
      script->script_5("3 -2.5 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -2.5 1.5 0");
      script->timer(96.5);

      script->script_1("SIDE_3");
      script->script_2("SIDE_3");
      script->script_3("SIDE_3");
      script->script_4("SIDE_3");
      script->script_5("SIDE_3");
      script->script_6("SIDE_3");
      script->script_7("SIDE_3");
      script->timer(98.5);

      script->script_1("2 -1 1.5 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-2 -1 1.5 0");
      script->script_5("3 -2.5 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -2.5 1.5 0");
      script->timer(100.0);

      script->script_1("2 -1 1.5 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-2 -1 1.5 0");
      script->script_5("3 -2.5 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -2.5 1.5 0");
      script->timer(101.0);

      script->script_1("2 -1 1.5 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-2 -1 1.5 0");
      script->script_5("3 -2.5 1.5 0");
      script->script_6("0 2 1.5 0");
      script->script_7("-3 -2.5 1.5 0");
      script->timer(102.0);

      script->script_1("3 1 1.5 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-3 1 1.5 0");
      script->script_5("2 -2.5 1.5 0");
      script->script_6("0 0 1.5 0");
      script->script_7("-2 -2.5 1.5 0");
      script->timer(103.0);

      script->script_1("3 1 1.5 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-3 1 1.5 0");
      script->script_5("2 -2.5 1.5 0");
      script->script_6("0 -2.5 1.5 0");
      script->script_7("-2 -2.5 1.5 0");
      script->timer(104.0);

      script->script_1("3 1 1.5 0");
      script->script_2("1 1 1.5 0");
      script->script_3("-1 1 1.5 0");
      script->script_4("-3 1 1.5 0");
      script->script_5("2 -2.5 1.5 0");
      script->script_6("0 -2.5 1.5 0");
      script->script_7("-2 -2.5 1.5 0");
      script->timer(105.0);

      script->script_1("3 1 1 0");
      script->script_2("1 1 1 0");
      script->script_3("-1 1 1 0");
      script->script_4("-3 1 1 0");
      script->script_5("2 -2.5 2 0");
      script->script_6("0 -2.5 2 0");
      script->script_7("-2 -2.5 2 0");
      script->timer(106.0);

      script->script_1("3 -2 1 0");
      script->script_2("1 -2 1 0");
      script->script_3("-1 -2 1 0");
      script->script_4("-3 -2 1 0");
      script->script_5("2 1 2 0");
      script->script_6("0 1 2 0");
      script->script_7("-2 1 2 0");
      script->timer(108.0);

      script->script_1("3 -2 2 0");
      script->script_2("1 -2 2 0");
      script->script_3("-1 -2 2 0");
      script->script_4("-3 -2 2 0");
      script->script_5("2 1 1.3 0");
      script->script_6("0 1 1.3 0");
      script->script_7("-2 1 1.3 0");
      script->timer(109.0);

      script->script_1("3 1 2 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-3 1 2 0");
      script->script_5("2 -2 1.3 0");
      script->script_6("0 -2 1.3 0");
      script->script_7("-2 -2 1.3 0");
      script->timer(111.0);

      script->script_1("3 1 1.3 0");
      script->script_2("1 1 1.3 0");
      script->script_3("-1 1 1.3 0");
      script->script_4("-3 1 1.3 0");
      script->script_5("2 -2 2 0");
      script->script_6("0 -2 2 0");
      script->script_7("-2 -2 2 0");
      script->timer(112.0);

      script->script_1("3 -2 1.3 0");
      script->script_2("1 -2 1.3 0");
      script->script_3("-1 -2 1.3 0");
      script->script_4("-3 -2 1.3 0");
      script->script_5("2 1 2 0");
      script->script_6("0 1 2 0");
      script->script_7("-2 1 2 0");
      script->timer(114.0);

      script->script_1("3 -2 2 0");
      script->script_2("1 -2 2 0");
      script->script_3("-1 2 2 0");
      script->script_4("-3 2 2 0");
      script->script_5("2 1 1.3 0");
      script->script_6("0 1 1.3 0");
      script->script_7("-2 1 1.3 0");
      script->timer(115.0);

      script->script_1("3 1 2 0");
      script->script_2("1 1 2 0");
      script->script_3("-1 1 2 0");
      script->script_4("-3 1 2 0");
      script->script_5("2 -2 1.3 0");
      script->script_6("0 -2 1.3 0");
      script->script_7("-2 -2 1.3 0");
      script->timer(117.0);

      script->script_1("3 2 1.5 0");
      script->script_2("1 2 1.5 0");
      script->script_3("-1 2 1.5 0");
      script->script_4("-3 2 1.5 0");
      script->script_5("2 0.5 1.3 0");
      script->script_6("0 0.5 1.3 0");
      script->script_7("-2 0.5 1.3 0");
      script->timer(118.0);

      script->script_1("3 2 1.5 0");
      script->script_2("1 2 1.5 0");
      script->script_3("-1 2 1.5 0");
      script->script_4("-3 2 1.5 0");
      script->script_5("FLIP_BACKWARD");
      script->script_6("FLIP_BACKWARD");
      script->script_7("FLIP_BACKWARD");
      script->timer(119.0);

      script->script_1("3 1 1.5 0");
      script->script_2("1 1 1.5 0");
      script->script_3("-1 1 1.5 0");
      script->script_4("-3 1 1.5 0");
      script->script_5("2 -1 1.5 0");
      script->script_6("0 -1 1.5 0");
      script->script_7("-2 -1 1.5 0");
      script->timer(122.0);

      /* Landing */
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
      script->timer(125.0);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "Third_script");
  int flattrim = 0;
  bool checksome = false;
  std_msgs::Empty m;
  ros::NodeHandle nh;
  ros::Publisher pub[9];

  script = new Script();
  script->advertise(nh);
  script->subscribe(nh);
  pub[0] = nh.advertise<std_msgs::Empty>("/bebop_1/flattrim", 1);
  pub[1] = nh.advertise<std_msgs::Empty>("/bebop_2/flattrim", 1);
  pub[2] = nh.advertise<std_msgs::Empty>("/bebop_3/flattrim", 1);
  pub[3] = nh.advertise<std_msgs::Empty>("/bebop_4/flattrim", 1);
  pub[4] = nh.advertise<std_msgs::Empty>("/bebop_5/flattrim", 1);
  pub[5] = nh.advertise<std_msgs::Empty>("/bebop_6/flattrim", 1);
  pub[6] = nh.advertise<std_msgs::Empty>("/bebop_7/flattrim", 1);

  ros::Rate loop_rate(30);

  while (ros::ok())
  {
    ros::spinOnce();

    if ( flattrim < 10) {
      pub[0].publish(m);
      pub[1].publish(m);
      pub[2].publish(m);
      pub[3].publish(m);
      pub[4].publish(m);
      pub[5].publish(m);
      pub[6].publish(m);
      flattrim++;
    }

    if ( script->script_flag ) {
      script->super_sub.shutdown();
      write_scrip_here();
      ros::Duration(3).sleep();
      script->script_flag = false;
      checksome = true;
    }
    if ( checksome ) {
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
      if (ros::ok()) ros::Duration(2).sleep();
    }

    loop_rate.sleep();
  }
  delete script;

  return 0;
}
