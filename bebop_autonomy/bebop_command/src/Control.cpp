#include "Control.h"
#include "Camera.h"
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <math.h>
#include <ros/ros.h>
#include <sstream>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <std_msgs/UInt8.h>
#include <string>

// 명령어 정의
#define Flip_forward 1
#define Flip_backword 2
#define FLip_left 3
#define FLip_right 4
#define DO_LAND 5
#define DO_TAKEOFF 6
#define DO_RESET 8
#define SIDE 10
#define UPDOWN 11

// x,y,z, yaw에 대한 PID 계수 정의
#define Kp_x 0.55
#define Ki_x 0.0001
#define Kd_x 2.65 // 2.35

#define Kp_y 0.55
#define Ki_y 0.0001
#define Kd_y 2.65 // 2.35

#define Kp_z 1.5
#define Ki_z 0.0003
#define Kd_z 0.97

#define Kp_yaw 0.043
#define Ki_yaw 0
#define Kd_yaw 0.024

// 프로그램 loop 시간 정의
#define dt 0.05

// Control 헤더파일로부터 클래스 불러오기
Control *control;

// ROS 내의 타이머 함수 이용하여 모션 제작
void Motion_timer(const ros::TimerEvent &event) {
  // 1.5초 동안 이*착륙 명령 수행 (40 x 0.05 = 2초)
  if (control->takeoffNland_counter < 40) {
    // 이륙 명령이 들어왔는지 확인
    if (control->TakeoffFlag[0])
      control->doMisc(DO_TAKEOFF, 0, control->pub_1[LAND],
                      control->pub_1[TAKEOFF]);
    if (control->TakeoffFlag[1])
      control->doMisc(DO_TAKEOFF, 1, control->pub_2[LAND],
                      control->pub_2[TAKEOFF]);
    if (control->TakeoffFlag[2])
      control->doMisc(DO_TAKEOFF, 2, control->pub_3[LAND],
                      control->pub_3[TAKEOFF]);
    if (control->TakeoffFlag[3])
      control->doMisc(DO_TAKEOFF, 3, control->pub_4[LAND],
                      control->pub_4[TAKEOFF]);
    if (control->TakeoffFlag[4])
      control->doMisc(DO_TAKEOFF, 4, control->pub_5[LAND],
                      control->pub_5[TAKEOFF]);
    if (control->TakeoffFlag[5])
      control->doMisc(DO_TAKEOFF, 5, control->pub_6[LAND],
                      control->pub_6[TAKEOFF]);
    if (control->TakeoffFlag[6])
      control->doMisc(DO_TAKEOFF, 6, control->pub_7[LAND],
                      control->pub_7[TAKEOFF]);
    // 착륙 명령이 들어왔는지 확인
    if (control->LandFlag[0])
      control->doMisc(DO_LAND, 0, control->pub_1[LAND],
                      control->pub_1[TAKEOFF]);
    if (control->LandFlag[1])
      control->doMisc(DO_LAND, 1, control->pub_2[LAND],
                      control->pub_2[TAKEOFF]);
    if (control->LandFlag[2])
      control->doMisc(DO_LAND, 2, control->pub_3[LAND],
                      control->pub_3[TAKEOFF]);
    if (control->LandFlag[3])
      control->doMisc(DO_LAND, 3, control->pub_4[LAND],
                      control->pub_4[TAKEOFF]);
    if (control->LandFlag[4])
      control->doMisc(DO_LAND, 4, control->pub_5[LAND],
                      control->pub_5[TAKEOFF]);
    if (control->LandFlag[5])
      control->doMisc(DO_LAND, 5, control->pub_6[LAND],
                      control->pub_6[TAKEOFF]);
    if (control->LandFlag[6])
      control->doMisc(DO_LAND, 6, control->pub_7[LAND],
                      control->pub_7[TAKEOFF]);
    // 이*착륙 명령어 시간 증가
    control->takeoffNland_counter++;
  }
}

// 명령어 char 타입으로 전환 후, 리턴
int Converter(short drone_number, const char *input) {
  char flip_forward = 'F';
  char flip_backward = 'B';
  char flip_left = 'E';
  char flip_right = 'I';
  char land = 'L';
  char take_off = 'T';
  char side = 'S';
  char updown = 'U';

  if (input[0] == 'F') {
    if (input[5] == flip_forward)
      return 1;
    else if (input[5] == flip_backward)
      return 2;
    else if (input[6] == flip_left)
      return 3;
    else if (input[6] == flip_right)
      return 4;
  } else if (input[0] == land)
    return 5;
  else if (input[0] == take_off)
    return 6;
  else if (input[0] == side) {
    if (input[5] == 'L')
      control->direction[drone_number] = 0;
    else if (input[5] == 'R')
      control->direction[drone_number] = 1;
    else if (input[5] == '1')
      control->repeat[drone_number] = 1;
    else if (input[5] == '2')
      control->repeat[drone_number] = 2;
    else if (input[5] == '3')
      control->repeat[drone_number] = 3;
    else if (input[5] == '4')
      control->repeat[drone_number] = 4;
    else if (input[5] == '5')
      control->repeat[drone_number] = 5;
    else if (input[5] == '6')
      control->repeat[drone_number] = 6;
    else if (input[5] == '7')
      control->repeat[drone_number] = 7;
    else
      control->repeat[drone_number] = 8;
    return 10;
  } else if (input[0] == updown) {
    if (input[7] == 'G')
      control->repeat[drone_number] = 0;
    else if (input[7] == '1')
      control->repeat[drone_number] = 1;
    else if (input[7] == '2')
      control->repeat[drone_number] = 2;
    else if (input[7] == '3')
      control->repeat[drone_number] = 3;
    else if (input[7] == '4')
      control->repeat[drone_number] = 4;
    else if (input[7] == '5')
      control->repeat[drone_number] = 5;
    else if (input[7] == '6')
      control->repeat[drone_number] = 6;
    else if (input[7] == '7')
      control->repeat[drone_number] = 7;
    else
      control->repeat[drone_number] = 8;
    return 11;
  } else
    return 0;
}

// Degree를 Radian으로 변환
double Deg2Rad(double deg) { return deg * M_PI / 180; }

// 입력된 명령어 판별 및 입력된 명령 함수 수행
void Control::key(short drone_number, const char *transmit,
                  ros::Publisher pub) {
  // flag에 변환된 명령어 저장
  int flag = Converter(drone_number, transmit);

  // switch문을 사용하여 입력된 명령 함수 수행
  if (transmit != NULL)
    switch (flag) {
    case 1:
      doFlip(0, pub);
      break;

    case 2:
      doFlip(1, pub);
      break;

    case 3:
      doFlip(2, pub);
      break;

    case 4:
      doFlip(3, pub);
      break;

    case DO_LAND:
      control->LandFlag[drone_number] = 1;
      control->takeoffNland_counter = 0;
      break;

    case DO_TAKEOFF:
      control->TakeoffFlag[drone_number] = 1;
      control->takeoffNland_counter = 0;
      break;

    case SIDE:
      control->SideFlag[drone_number] = 1;
      break;

    case UPDOWN:
      control->UpDownFlag[drone_number] = 1;
      break;

    default:
      return;
    }
}

// 속도, 이*착륙, 비상착륙, 플립 명령어를 드론으로 퍼블리쉬
void Control::advertise(ros::NodeHandle &nh) {
  pub_1[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_1/cmd_vel", 1);
  pub_1[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_1/takeoff", 1);
  pub_1[LAND] = nh.advertise<std_msgs::Empty>("bebop_1/land", 1);
  pub_1[RESET] = nh.advertise<std_msgs::Empty>("bebop_1/reset", 1);
  pub_1[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_1/flip", 1);

  pub_2[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_2/cmd_vel", 1);
  pub_2[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_2/takeoff", 1);
  pub_2[LAND] = nh.advertise<std_msgs::Empty>("bebop_2/land", 1);
  pub_2[RESET] = nh.advertise<std_msgs::Empty>("bebop_2/reset", 1);
  pub_2[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_2/flip", 1);

  pub_3[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_3/cmd_vel", 1);
  pub_3[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_3/takeoff", 1);
  pub_3[LAND] = nh.advertise<std_msgs::Empty>("bebop_3/land", 1);
  pub_3[RESET] = nh.advertise<std_msgs::Empty>("bebop_3/reset", 1);
  pub_3[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_3/flip", 1);

  pub_4[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_4/cmd_vel", 1);
  pub_4[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_4/takeoff", 1);
  pub_4[LAND] = nh.advertise<std_msgs::Empty>("bebop_4/land", 1);
  pub_4[RESET] = nh.advertise<std_msgs::Empty>("bebop_4/reset", 1);
  pub_4[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_4/flip", 1);

  pub_5[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_5/cmd_vel", 1);
  pub_5[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_5/takeoff", 1);
  pub_5[LAND] = nh.advertise<std_msgs::Empty>("bebop_5/land", 1);
  pub_5[RESET] = nh.advertise<std_msgs::Empty>("bebop_5/reset", 1);
  pub_5[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_5/flip", 1);

  pub_6[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_6/cmd_vel", 1);
  pub_6[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_6/takeoff", 1);
  pub_6[LAND] = nh.advertise<std_msgs::Empty>("bebop_6/land", 1);
  pub_6[RESET] = nh.advertise<std_msgs::Empty>("bebop_6/reset", 1);
  pub_6[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_6/flip", 1);

  pub_7[VELOCITY] = nh.advertise<geometry_msgs::Twist>("bebop_7/cmd_vel", 1);
  pub_7[TAKEOFF] = nh.advertise<std_msgs::Empty>("bebop_7/takeoff", 1);
  pub_7[LAND] = nh.advertise<std_msgs::Empty>("bebop_7/land", 1);
  pub_7[RESET] = nh.advertise<std_msgs::Empty>("bebop_7/reset", 1);
  pub_7[FLIP] = nh.advertise<std_msgs::UInt8>("bebop_7/flip", 1);
}

// x는 수평축, y는 수칙축
// 카메라에서 받은 정보를 이용하여 드론을 조종하는 함수
void Control::position_control(short drone_number, ros::Publisher pub) {
  if (SideFlag[drone_number])
    LeftNRight(drone_number);
  if (UpDownFlag[drone_number])
    UpDown(drone_number);

  double x_gap = x_des[drone_number] - x[drone_number];
  double y_gap = y_des[drone_number] - y[drone_number];
  double z_gap = z_des[drone_number] - z[drone_number];
  double yaw_gap = 0;
  // yaw축을 -180 ~ 180까지 정의하는 구간
  if (abs(yaw_des[drone_number] - yaw[drone_number]) <= 180)
    yaw_gap = yaw_des[drone_number] - yaw[drone_number];
  else {
    if (yaw_des[drone_number] >= yaw[drone_number])
      yaw_gap = -yaw[drone_number] - (360 - yaw_des[drone_number]);
    else
      yaw_gap = yaw_des[drone_number] + (360 - yaw[drone_number]);
  }

  // 최대 속도는 1
  // 위에서 정한 -180~180의 yaw를 0-360으로 변환하여 속도 정의
  double x_speed = (-sin(Deg2Rad(yaw[drone_number])) * x_gap +
                    cos(Deg2Rad(yaw[drone_number])) * y_gap);
  double y_speed = (-cos(Deg2Rad(yaw[drone_number])) * x_gap -
                    sin(Deg2Rad(yaw[drone_number])) * y_gap);

  // PID 연산
  double P_control_x = Kp_x * x_speed;
  I_control_x[drone_number] = I_control_x[drone_number] + Ki_x * x_speed * dt;
  double D_control_x = Kd_x * (x_speed - x_speed_old[drone_number]) / dt;

  double P_control_y = Kp_y * y_speed;
  I_control_y[drone_number] = I_control_y[drone_number] + Ki_y * y_speed * dt;
  double D_control_y = Kd_y * (y_speed - y_speed_old[drone_number]) / dt;

  double P_control_z = Kp_z * z_gap;
  I_control_z[drone_number] = I_control_z[drone_number] + Ki_z * z_gap * dt;
  double D_control_z = Kd_z * (z_gap - z_gap_old[drone_number]) / dt;

  double P_control_yaw = Kp_yaw * yaw_gap;
  I_control_yaw[drone_number] =
      I_control_yaw[drone_number] + Ki_yaw * yaw_gap * dt;
  double D_control_yaw = Kd_yaw * (yaw_gap - yaw_gap_old[drone_number]) / dt;

  x_speed_old[drone_number] = x_speed;
  y_speed_old[drone_number] = y_speed;
  z_gap_old[drone_number] = z_gap;
  yaw_gap_old[drone_number] = yaw_gap;

  double x_value = P_control_x + I_control_x[drone_number] + D_control_x;
  double y_value = P_control_y + I_control_y[drone_number] + D_control_y;
  double z_value = P_control_z + I_control_z[drone_number] + D_control_z;
  double yaw_value =
      P_control_yaw + I_control_yaw[drone_number] + D_control_yaw;

  geometry_msgs::Twist input_speed;

  input_speed.linear.x = x_value;
  input_speed.linear.y = y_value;
  input_speed.linear.z = z_value;
  input_speed.angular.z = yaw_value;

  // 최종 속도 명령을 드론으로 보낸다.
  pub.publish(input_speed);
}

// 이*착륙, 비상착륙에 관한 명령 함수
void Control::doMisc(short type, short drone_number, ros::Publisher land_pub,
                     ros::Publisher takeoff_pub) {
  if (type == DO_LAND) {
    // 착륙전 호버링을 위한 변수 설정
    // 착륙 명령을 받는 순간 위치를 유지하며 1.4초 동안 지상에서 10 센치미터로
    // 하강
    if (takeoffNland_counter < 28) {
      z_des[drone_number] = 0.1;
    } else if (takeoffNland_counter < 33) {
      camera_node->takeoff_ready[drone_number] = 0;
      manner[drone_number] = 0;
      std_msgs::Empty m;
      land_pub.publish(m);
    } else
      LandFlag[drone_number] = 0;
  } else if (type == DO_TAKEOFF && camera_node->takeoff_ready[drone_number]) {
    // 0.25초 동안 이륙 수행 명령 전송
    std_msgs::Empty m;
    takeoff_pub.publish(m);

    if (manner[drone_number] == 0) {
      x_des[drone_number] = x[drone_number];
      y_des[drone_number] = y[drone_number];
      z_des[drone_number] = 1.2;
      yaw_des[drone_number] = 0;

      manner[drone_number] = 1;
    }

    if (takeoffNland_counter > 5)
      TakeoffFlag[drone_number] = 0;
  }
}

// 플립 명령 수행 함수
// 들어온 플립 방향을 m에 저장 후 드론으로 해당 방향 플립 명령어 전송
void Control::doFlip(short type, ros::Publisher pub) {
  std_msgs::UInt8 m;
  m.data = type;
  pub.publish(m);
}

// 좌우로 까딱거리는 명령 수행 함수
void Control::LeftNRight(short drone_number) {
  if (repeat[drone_number] == 0) {
    if (direction[drone_number]) {
      if (turn_switch[drone_number] == 0) {
        x_tmp[drone_number] = x_des[drone_number];
        y_tmp[drone_number] = y_des[drone_number];

        x_des[drone_number] =
            x_tmp[drone_number] + 0.08 * cos(Deg2Rad(yaw_des[drone_number]));
        y_des[drone_number] =
            y_tmp[drone_number] + 0.08 * sin(Deg2Rad(yaw_des[drone_number]));

        turn_switch[drone_number]++;
      } else if (turn_switch[drone_number] == 1) {
        if (pow((x_des[drone_number] - x[drone_number]), 2) +
                pow((y_des[drone_number] - y[drone_number]), 2) <
            1e-4) {
          x_des[drone_number] = x_tmp[drone_number];
          y_des[drone_number] = y_tmp[drone_number];

          turn_switch[drone_number]++;
        }
      } else if (turn_switch[drone_number] == 1) {
        SideFlag[drone_number] = 0;
        turn_switch[drone_number] = 0;
      }
    } else {
      if (turn_switch[drone_number] == 0) {
        x_tmp[drone_number] = x_des[drone_number];
        y_tmp[drone_number] = y_des[drone_number];

        x_des[drone_number] =
            x_tmp[drone_number] - 0.08 * cos(Deg2Rad(yaw_des[drone_number]));
        y_des[drone_number] =
            y_tmp[drone_number] - 0.08 * sin(Deg2Rad(yaw_des[drone_number]));

        turn_switch[drone_number]++;
      } else if (turn_switch[drone_number] == 1) {
        if (pow((x_des[drone_number] - x[drone_number]), 2) +
                pow((y_des[drone_number] - y[drone_number]), 2) <
            1e-4) {
          x_des[drone_number] = x_tmp[drone_number];
          y_des[drone_number] = y_tmp[drone_number];

          turn_switch[drone_number]++;
        }
      } else if (turn_switch[drone_number] == 1) {
        SideFlag[drone_number] = 0;
        turn_switch[drone_number] = 0;
      }
    }
  } else {
    // repeat의 크기 만큼 앞뒤로 까딱거리는 명령 수행
    if (repeat_count[drone_number] < repeat[drone_number]) {
      if (turn_switch[drone_number] == 0) {
        x_tmp[drone_number] = x_des[drone_number];
        y_tmp[drone_number] = y_des[drone_number];

        x_des[drone_number] =
            x_tmp[drone_number] + 0.08 * cos(Deg2Rad(yaw_des[drone_number]));
        y_des[drone_number] =
            y_tmp[drone_number] + 0.08 * sin(Deg2Rad(yaw_des[drone_number]));

        turn_switch[drone_number]++;
      } else if (turn_switch[drone_number] == 1) {
        if (pow((x_des[drone_number] - x[drone_number]), 2) +
                pow((y_des[drone_number] - y[drone_number]), 2) <
            1e-4) {
          x_des[drone_number] =
              x_tmp[drone_number] - 0.08 * cos(Deg2Rad(yaw_des[drone_number]));
          y_des[drone_number] =
              y_tmp[drone_number] - 0.08 * sin(Deg2Rad(yaw_des[drone_number]));

          turn_switch[drone_number]++;
        }
      } else if (turn_switch[drone_number] == 2) {
        if (pow((x_des[drone_number] - x[drone_number]), 2) +
                pow((y_des[drone_number] - y[drone_number]), 2) <
            1e-4) {
          turn_switch[drone_number] = 0;
          repeat_count[drone_number]++;
        }
      }
    } else {
      x_des[drone_number] = x_tmp[drone_number];
      y_des[drone_number] = y_tmp[drone_number];
      SideFlag[drone_number] = false;
      repeat_count[drone_number] = 0;
    }
  }
}

// 앞뒤로 까딱거리는 모션 수행 함수
void Control::UpDown(short drone_number) {
  // 인사하는 동작 수행
  if (repeat[drone_number] == 0) {
    if (turn_switch[drone_number] == 0) {
      x_tmp[drone_number] = x_des[drone_number];
      y_tmp[drone_number] = y_des[drone_number];

      x_des[drone_number] =
          x_tmp[drone_number] - 0.08 * sin(Deg2Rad(yaw_des[drone_number]));
      y_des[drone_number] =
          y_tmp[drone_number] + 0.08 * cos(Deg2Rad(yaw_des[drone_number]));

      turn_switch[drone_number]++;
    } else if (turn_switch[drone_number] == 1) {
      if (pow((x_des[drone_number] - x[drone_number]), 2) +
              pow((y_des[drone_number] - y[drone_number]), 2) <
          1e-4) {
        x_des[drone_number] = x_tmp[drone_number];
        y_des[drone_number] = y_tmp[drone_number];

        turn_switch[drone_number]++;
      }
    } else if (turn_switch[drone_number] == 2) {
      UpDownFlag[drone_number] = 0;
      turn_switch[drone_number] = 0;
    }
  } else {
    // repeat의 크기 만큼 앞뒤로 까딱거리는 명령 수행
    if (repeat_count[drone_number] < repeat[drone_number]) {
      if (turn_switch[drone_number] == 0) {
        x_tmp[drone_number] = x_des[drone_number];
        y_tmp[drone_number] = y_des[drone_number];

        x_des[drone_number] =
            x_tmp[drone_number] - 0.08 * sin(Deg2Rad(yaw_des[drone_number]));
        y_des[drone_number] =
            y_tmp[drone_number] + 0.08 * cos(Deg2Rad(yaw_des[drone_number]));

        turn_switch[drone_number]++;
      } else if (turn_switch[drone_number] == 1) {
        if (pow((x_des[drone_number] - x[drone_number]), 2) +
                pow((y_des[drone_number] - y[drone_number]), 2) <
            1e-4) {
          x_des[drone_number] =
              x_tmp[drone_number] + 0.08 * sin(Deg2Rad(yaw_des[drone_number]));
          y_des[drone_number] =
              y_tmp[drone_number] - 0.08 * cos(Deg2Rad(yaw_des[drone_number]));

          turn_switch[drone_number]++;
        }
      } else if (turn_switch[drone_number] == 2) {
        if (pow((x_des[drone_number] - x[drone_number]), 2) +
                pow((y_des[drone_number] - y[drone_number]), 2) <
            1e-4) {
          turn_switch[drone_number] = 0;
          repeat_count[drone_number]++;
        }
      }
    } else {
      x_des[drone_number] = x_tmp[drone_number];
      y_des[drone_number] = y_tmp[drone_number];
      UpDownFlag[drone_number] = false;
      repeat_count[drone_number] = 0;
    }
  }
}
