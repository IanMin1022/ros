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

// 스크립트 입력
void write_scrip_here(void) {
  /* Take Off */
      script->timer(0);
      script->script_1("TAKE_OFF");
      script->script_2("TAKE_OFF");
      script->script_3("TAKE_OFF");
      script->script_4("TAKE_OFF");
      script->script_5("TAKE_OFF");
      script->script_6("TAKE_OFF");
      script->script_7("TAKE_OFF");

    /* Satrt_Hovering */
      script->timer(3);
      script->script_1("3 0.5 2 0");
      script->script_2("1 0.5 2 0");
      script->script_3("-1 0.5 2 0");
      script->script_4("-3 0.5 2 0");
      script->script_5("2 -2.5 2 0");
      script->script_6("0 -2.5 2 0");
      script->script_7("-2 -2.5 2 0");

    /* Moving */
      script->timer(8.0);
      script->script_1("0.0 2.2 1.5 0");
      script->script_2("-2.331438 1.887961 1.5 0");
      script->script_3("-2.934443 -0.623735 2.1 0");
      script->script_4("-1.361971 -2.67302 1.5 0");
      script->script_5("1.22021 -2.740636 1.5 0");
      script->script_6("2.897777 -0.776457 2.1 0");
      script->script_7("2.427051 1.763356 1.5 0");

    /* Making the Circle */
      script->timer(9.0);
      script->script_1("0.0 2.2 1.5 0");
      script->script_2("-1.942865 1.573301 1.5 0");
      script->script_3("-2.445369 -0.519779 1.5 0");
      script->script_4("-1.134976 -2.227516 1.5 0");
      script->script_5("1.016842 -2.283864 1.5 0");
      script->script_6("2.414815 -0.647048 1.5 0");
      script->script_7("2.022542 1.469463 1.5 0");

      script->timer(10.0);
      script->script_1("0.0 2.2 1.5 0");
      script->script_2("-1.720029 1.371678 1.5 0");
      script->script_3("-2.144841 -0.489546 1.5 0");
      script->script_4("-0.954544 -1.982132 1.5 0");
      script->script_5("0.954544 -1.982132 1.5 0");
      script->script_6("2.144841 -0.489546 1.5 0");
      script->script_7("1.720029 1.371678 1.5 0");

      script->timer(11.0);
      script->script_1("-1.1 1.905256 1.5 0");
      script->script_2("-2.175428 0.327893 1.5 0");
      script->script_3("-1.612714 -1.49638 1.5 0");
      script->script_4("0.164406 -2.193848 1.5 0");
      script->script_5("1.817725 -1.239304 1.5 0");
      script->script_6("2.10226 0.648461 1.5 0");
      script->script_7("0.80375 2.047922 1.5 0");

      script->timer(12.0);
      script->script_1("-1.905256 1.1 1.5 0");
      script->script_2("-2.047922 -0.80375 1.5 0");
      script->script_3("-0.648461 -2.10226 1.5 0");
      script->script_4("1.239304 -1.817725 1.5 0");
      script->script_5("2.193848 -0.164406 1.5 0");
      script->script_6("1.49638 1.612714 1.5 0");
      script->script_7("-0.327893 2.175428 1.5 0");

      script->timer(13.0);
      script->script_1("-2.2 0.0 1.5 0");
      script->script_2("-1.371678 -1.720029 1.5 0");
      script->script_3("0.489546 -2.144841 1.5 0");
      script->script_4("1.982132 -0.954544 1.5 0");
      script->script_5("1.982132 0.954544 1.5 0");
      script->script_6("0.489546 2.144841 1.5 0");
      script->script_7("-1.371678 1.720029 1.5 0");

      script->timer(14.0);
      script->script_1("-1.905256 -1.1 1.5 0");
      script->script_2("-0.327893 -2.175428 1.5 0");
      script->script_3("1.49638 -1.612714 1.5 0");
      script->script_4("2.193848 0.164406 1.5 0");
      script->script_5("1.239304 1.817725 1.5 0");
      script->script_6("-0.648461 2.10226 1.5 0");
      script->script_7("-2.047922 0.80375 1.5 0");

      script->timer(15.0);
      script->script_1("-1.1 -1.905256 1.5 0");
      script->script_2("0.80375 -2.047922 1.5 0");
      script->script_3("2.10226 -0.648461 1.5 0");
      script->script_4("1.817725 1.239304 1.5 0");
      script->script_5("0.164406 2.193848 1.5 0");
      script->script_6("-1.612714 1.49638 1.5 0");
      script->script_7("-2.175428 -0.327893 1.5 0");

      script->timer(16.0);
      script->script_1("0.0 -2.2 1.5 0");
      script->script_2("1.720029 -1.371678 1.5 0");
      script->script_3("2.144841 0.489546 1.5 0");
      script->script_4("0.954544 1.982132 1.5 0");
      script->script_5("-0.954544 1.982132 1.5 0");
      script->script_6("-2.144841 0.489546 1.5 0");
      script->script_7("-1.720029 -1.371678 1.5 0");

      script->timer(17.0);
      script->script_1("1.1 -1.905256 2.0 0");
      script->script_2("2.175428 -0.327893 2.0 0");
      script->script_3("1.612714 1.49638 2.0 0");
      script->script_4("-0.164406 2.193848 2.0 0");
      script->script_5("-1.817725 1.239304 2.0 0");
      script->script_6("-2.10226 -0.648461 2.0 0");
      script->script_7("-0.80375 -2.047922 2.0 0");

      script->timer(18.0);
      script->script_1("1.905256 -1.1 2.0 0");
      script->script_2("2.047922 0.80375 2.0 0");
      script->script_3("0.648461 2.10226 2.0 0");
      script->script_4("-1.239304 1.817725 2.0 0");
      script->script_5("-2.193848 0.164406 2.0 0");
      script->script_6("-1.49638 -1.612714 2.0 0");
      script->script_7("0.327893 -2.175428 2.0 0");

      script->timer(19.0);
      script->script_1("2.2 0.0 1.5 0");
      script->script_2("1.371678 1.720029 2.0 0");
      script->script_3("-0.489546 2.144841 2.0 0");
      script->script_4("-1.982132 0.954544 2.0 0");
      script->script_5("-1.982132 -0.954544 2.0 0");
      script->script_6("-0.489546 -2.144841 2.0 0");
      script->script_7("1.371678 -1.720029 2.0 0");

      script->timer(20.0);
      script->script_1("1.905256 1.1 2.0 0");
      script->script_2("0.327893 2.175428 2.0 0");
      script->script_3("-1.49638 1.612714 2.0 0");
      script->script_4("-2.193848 -0.164406 2.0 0");
      script->script_5("-1.239304 -1.817725 2.0 0");
      script->script_6("0.648461 -2.10226 2.0 0");
      script->script_7("2.047922 -0.80375 2.0 0");

      script->timer(21.0);
      script->script_1("1.1 1.905256 2.0 0");
      script->script_2("-0.80375 2.047922 2.0 0");
      script->script_3("-2.10226 0.648461 2.0 0");
      script->script_4("-1.817725 -1.239304 2.0 0");
      script->script_5("-0.164406 -2.193848 2.0 0");
      script->script_6("1.612714 -1.49638 2.0 0");
      script->script_7("2.175428 0.327893 2.0 0");

      script->timer(22.0);
      script->script_1("0.0 2.2 1.5 0");
      script->script_2("-1.720029 1.371678 2.0 0");
      script->script_3("-2.144841 -0.489546 2.0 0");
      script->script_4("-0.954544 -1.982132 2.0 0");
      script->script_5("0.954544 -1.982132 2.0 0");
      script->script_6("2.144841 -0.489546 2.0 0");
      script->script_7("1.720029 1.371678 2.0 0");

      script->timer(23.0);
      script->script_1("-1.1 1.905256 1.5 0");
      script->script_2("-2.175428 0.327893 2.0 0");
      script->script_3("-1.612714 -1.49638 2.0 0");
      script->script_4("0.164406 -2.193848 2.0 0");
      script->script_5("1.817725 -1.239304 2.0 0");
      script->script_6("2.10226 0.648461 2.0 0");
      script->script_7("0.80375 2.047922 1.5 0");

      script->timer(24.0);
      script->script_1("-1.905256 1.1 1.5 0");
      script->script_2("-2.047922 -0.80375 2.0 0");
      script->script_3("-0.648461 -2.10226 2.0 0");
      script->script_4("1.239304 -1.817725 2.0 0");
      script->script_5("2.193848 -0.164406 2.0 0");
      script->script_6("1.49638 1.612714 1.5 0");
      script->script_7("-0.327893 2.175428 1.5 0");

      script->timer(25.0);
      script->script_1("-2.2 0.0 1.5 0");
      script->script_2("-1.371678 -1.720029 2.0 0");
      script->script_3("0.489546 -2.144841 2.0 0");
      script->script_4("1.982132 -0.954544 2.0 0");
      script->script_5("1.982132 0.954544 1.5 0");
      script->script_6("0.489546 2.144841 1.5 0");
      script->script_7("-1.371678 1.720029 1.5 0");

      script->timer(26.0);
      script->script_1("-1.905256 -1.1 1.5 0");
      script->script_2("-0.327893 -2.175428 2.0 0");
      script->script_3("1.49638 -1.612714 2.0 0");
      script->script_4("2.193848 0.164406 1.5 0");
      script->script_5("1.239304 1.817725 1.5 0");
      script->script_6("-0.648461 2.10226 1.5 0");
      script->script_7("-2.047922 0.80375 1.5 0");

      script->timer(27.0);
      script->script_1("-1.1 -1.905256 1.5 0");
      script->script_2("0.80375 -2.047922 2.0 0");
      script->script_3("2.10226 -0.648461 1.5 0");
      script->script_4("1.817725 1.239304 1.5 0");
      script->script_5("0.164406 2.193848 1.5 0");
      script->script_6("-1.612714 1.49638 1.5 0");
      script->script_7("-2.175428 -0.327893 1.5 0");

      script->timer(28.0);
      script->script_1("0.0 -2.2 1.5 0");
      script->script_2("1.720029 -1.371678 1.5 0");
      script->script_3("2.144841 0.489546 1.5 0");
      script->script_4("0.954544 1.982132 1.5 0");
      script->script_5("-0.954544 1.982132 1.5 0");
      script->script_6("-2.144841 0.489546 1.5 0");
      script->script_7("-1.720029 -1.371678 1.5 0");

      script->timer(29.0);
      script->script_1("1.1 -1.905256 1.7 0");
      script->script_2("2.175428 -0.327893 2.0 0");
      script->script_3("1.612714 1.49638 1.7 0");
      script->script_4("-0.164406 2.193848 2.0 0");
      script->script_5("-1.817725 1.239304 1.7 0");
      script->script_6("-2.10226 -0.648461 2.0 0");
      script->script_7("-0.80375 -2.047922 1.7 0");

      script->timer(30.0);
      script->script_1("1.905256 -1.1 1.7 0");
      script->script_2("2.047922 0.80375 1.7 0");
      script->script_3("0.648461 2.10226 1.7 0");
      script->script_4("-1.239304 1.817725 1.7 0");
      script->script_5("-2.193848 0.164406 1.7 0");
      script->script_6("-1.49638 -1.612714 1.7 0");
      script->script_7("0.327893 -2.175428 1.7 0");

      script->timer(31.0);
      script->script_1("2.2 0.0 2.0 0");
      script->script_2("1.371678 1.720029 1.7 0");
      script->script_3("-0.489546 2.144841 2.0 0");
      script->script_4("-1.982132 0.954544 1.7 0");
      script->script_5("-1.982132 -0.954544 2.0 0");
      script->script_6("-0.489546 -2.144841 1.7 0");
      script->script_7("1.371678 -1.720029 2.0 0");

      script->timer(32.0);
      script->script_1("1.905256 1.1 1.7 0");
      script->script_2("0.327893 2.175428 2.0 0");
      script->script_3("-1.49638 1.612714 1.7 0");
      script->script_4("-2.193848 -0.164406 2.0 0");
      script->script_5("-1.239304 -1.817725 1.7 0");
      script->script_6("0.648461 -2.10226 2.0 0");
      script->script_7("2.047922 -0.80375 1.7 0");

      script->timer(33.0);
      script->script_1("1.1 1.905256 2.0 0");
      script->script_2("-0.80375 2.047922 1.7 0");
      script->script_3("-2.10226 0.648461 2.0 0");
      script->script_4("-1.817725 -1.239304 1.7 0");
      script->script_5("-0.164406 -2.193848 2.0 0");
      script->script_6("1.612714 -1.49638 1.7 0");
      script->script_7("2.175428 0.327893 2.0 0");

      script->timer(34.0);
      script->script_1("0.0 2.2 1.7 0");
      script->script_2("-1.720029 1.371678 2.0 0");
      script->script_3("-2.144841 -0.489546 1.7 0");
      script->script_4("-0.954544 -1.982132 2.0 0");
      script->script_5("0.954544 -1.982132 1.7 0");
      script->script_6("2.144841 -0.489546 2.0 0");
      script->script_7("1.720029 1.371678 1.7 0");

      script->timer(35.0);
      script->script_1("-1.1 1.905256 2.0 0");
      script->script_2("-2.175428 0.327893 1.7 0");
      script->script_3("-1.612714 -1.49638 2.0 0");
      script->script_4("0.164406 -2.193848 1.7 0");
      script->script_5("1.817725 -1.239304 2.0 0");
      script->script_6("2.10226 0.648461 1.7 0");
      script->script_7("0.80375 2.047922 2.0 0");

      script->timer(36.0);
      script->script_1("-1.905256 1.1 1.7 0");
      script->script_2("-2.047922 -0.80375 2.0 0");
      script->script_3("-0.648461 -2.10226 1.7 0");
      script->script_4("1.239304 -1.817725 2.0 0");
      script->script_5("2.193848 -0.164406 1.7 0");
      script->script_6("1.49638 1.612714 2.0 0");
      script->script_7("-0.327893 2.175428 1.7 0");

      script->timer(37.0);
      script->script_1("-2.2 0.0 1.5 0");
      script->script_2("-1.371678 -1.720029 1.5 0");
      script->script_3("0.489546 -2.144841 1.5 0");
      script->script_4("1.982132 -0.954544 1.5 0");
      script->script_5("1.982132 0.954544 1.5 0");
      script->script_6("0.489546 2.144841 1.5 0");
      script->script_7("-1.371678 1.720029 1.5 0");

      script->timer(38.0);
      script->script_1("-1.905256 -1.1 1.5 0");
      script->script_2("-0.327893 -2.175428 1.5 0");
      script->script_3("1.49638 -1.612714 1.5 0");
      script->script_4("2.193848 0.164406 2.0 0");
      script->script_5("1.239304 1.817725 1.5 0");
      script->script_6("-0.648461 2.10226 1.5 0");
      script->script_7("-2.047922 0.80375 1.5 0");

      script->timer(39.0);
      script->script_1("-1.1 -1.905256 1.5 0");
      script->script_2("0.80375 -2.047922 1.5 0");
      script->script_3("2.10226 -0.648461 2.0 0");
      script->script_4("1.817725 1.239304 2.0 0");
      script->script_5("0.164406 2.193848 1.5 0");
      script->script_6("-1.612714 1.49638 1.5 0");
      script->script_7("-2.175428 -0.327893 1.5 0");

      script->timer(40.0);
      script->script_1("0.0 -2.2 1.5 0");
      script->script_2("1.720029 -1.371678 2.0 0");
      script->script_3("2.144841 0.489546 2.0 0");
      script->script_4("0.954544 1.982132 2.0 0");
      script->script_5("-0.954544 1.982132 1.5 0");
      script->script_6("-2.144841 0.489546 1.5 0");
      script->script_7("-1.720029 -1.371678 1.5 0");

      script->timer(41.0);
      script->script_1("1.1 -1.905256 2.0 0");
      script->script_2("2.175428 -0.327893 2.0 0");
      script->script_3("1.612714 1.49638 2.0 0");
      script->script_4("-0.164406 2.193848 2.0 0");
      script->script_5("-1.817725 1.239304 1.5 0");
      script->script_6("-2.10226 -0.648461 1.5 0");
      script->script_7("-0.80375 -2.047922 1.5 0");

      script->timer(42.0);
      script->script_1("1.905256 -1.1 2.0 0");
      script->script_2("2.047922 0.80375 2.0 0");
      script->script_3("0.648461 2.10226 2.0 0");
      script->script_4("-1.239304 1.817725 2.0 0");
      script->script_5("-2.193848 0.164406 1.5 0");
      script->script_6("-1.49638 -1.612714 1.5 0");
      script->script_7("0.327893 -2.175428 2.0 0");

      script->timer(43.0);
      script->script_1("2.2 0.0 2.0 0");
      script->script_2("1.371678 1.720029 2.0 0");
      script->script_3("-0.489546 2.144841 2.0 0");
      script->script_4("-1.982132 0.954544 2.0 0");
      script->script_5("-1.982132 -0.954544 1.5 0");
      script->script_6("-0.489546 -2.144841 2.0 0");
      script->script_7("1.371678 -1.720029 2.0 0");

      script->timer(44.0);
      script->script_1("1.905256 1.1 2.0 0");
      script->script_2("0.327893 2.175428 2.0 0");
      script->script_3("-1.49638 1.612714 2.0 0");
      script->script_4("-2.193848 -0.164406 2.0 0");
      script->script_5("-1.239304 -1.817725 2.0 0");
      script->script_6("0.648461 -2.10226 2.0 0");
      script->script_7("2.047922 -0.80375 2.0 0");

      script->timer(45.0);
      script->script_1("1.1 1.905256 1.5 0");
      script->script_2("-0.80375 2.047922 1.5 0");
      script->script_3("-2.10226 0.648461 1.5 0");
      script->script_4("-1.817725 -1.239304 1.5 0");
      script->script_5("-0.164406 -2.193848 1.5 0");
      script->script_6("1.612714 -1.49638 1.5 0");
      script->script_7("2.175428 0.327893 1.5 0");

      script->timer(46.0);
      script->script_1("0.0 2.2 1.5 0");
      script->script_2("-1.720029 1.371678 1.5 0");
      script->script_3("-2.144841 -0.489546 1.5 0");
      script->script_4("-0.954544 -1.982132 1.5 0");
      script->script_5("0.954544 -1.982132 1.5 0");
      script->script_6("2.144841 -0.489546 1.5 0");
      script->script_7("1.720029 1.371678 1.5 0");


    /* Flip */
      script->timer(47.0);
      script->script_1("0 2.2 1.5 0");
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
      script->script_1("0 2.2 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -2 1.5 0");
      script->script_6("2 0 1.5 0");
      script->script_7("2 2 1.5 0");

      script->timer(60.0);
      script->script_1("0 2.2 1.5 0");
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
      script->script_1("0 2 1.5 0");
      script->script_2("-2 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -3 1.5 0");
      script->script_6("2 -1 1.5 0");
      script->script_7("2 1 1.5 0");

      script->timer(67.0);
      script->script_1("3 2 1.5 0");
      script->script_2("1 2 1.5 0");
      script->script_3("-2 0 1.5 0");
      script->script_4("-2 -2 1.5 0");
      script->script_5("2 -3 1.5 0");
      script->script_6("2 -1 1.5 0");
      script->script_7("2 1 1.5 0");

      script->timer(68.0);
      script->script_1("3 2 1.5 0");
      script->script_2("1 2 1.5 0");
      script->script_3("-1 2 1.5 0");
      script->script_4("-3 2 1.5 0");
      script->script_5("2 -3 1.5 0");
      script->script_6("2 -1 1.5 0");
      script->script_7("-3 -1 1.5 0");

      script->timer(69.0);
      script->script_1("3 2 1.5 0");
      script->script_2("1 2 1.5 0");
      script->script_3("-1 2 1.5 0");
      script->script_4("-3 2 1.5 0");
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
      script->script_7("-3 -2.5 1.5 0");

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
      script->script_3("-1 -2 2 0");
      script->script_4("-3 -2 2 0");
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
      script->script_5("2 -0.5 1.3 0");
      script->script_6("0 -0.5 1.3 0");
      script->script_7("-2 -0.5 1.3 0");

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

    /* Landing */
      script->timer(122.0);
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "First_script");
  int flattrim = 0;
  bool checksome = false;
  std_msgs::Empty m;
  ros::NodeHandle nh;
  ros::Publisher pub[9];

  script = new Script();
  script->advertise(nh);
  script->subscribe(nh);
  // 플랫트림 세팅 퍼블리쉬
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

    // 드론 이륙전 플랫트림 세팅
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
    // 스크립트 읽고 착륙 준비
    if ( script->script_flag ) {
      script->super_sub.shutdown();
      write_scrip_here();
      ros::Duration(3).sleep();
      script->script_flag = false;
      checksome = true;
    }
    // 스크립트가 끝난 후 착륙 실행
    if ( checksome ) {
      script->script_1("LAND");
      script->script_2("LAND");
      script->script_3("LAND");
      script->script_4("LAND");
      script->script_5("LAND");
      script->script_6("LAND");
      script->script_7("LAND");
      if (ros::ok()) ros::Duration(1).sleep();
    }

    loop_rate.sleep();
  }
  delete script;

  return 0;
}
