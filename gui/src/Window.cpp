#include "State.h"
#include "Window.h"
#include <SDL2/SDL_ttf.h>
#include <iomanip>
#include <iomanip>
#include <math.h>
#include <ros/ros.h>
#include <sstream>
#include <stdlib.h>

#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 368
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 500

#define PREC(p) std::fixed << std::setprecision(p)

Window *window;

std::string Window::font_path;

GUIC *watch;

GUIC *wifi_title;
GUIC *batt_title;

GUIC *script_title;

GUIC *batt_1;
GUIC *batt_2;
GUIC *batt_3;
GUIC *batt_4;
GUIC *batt_5;
GUIC *batt_6;
GUIC *batt_7;

GUIC *wifi_1;
GUIC *wifi_2;
GUIC *wifi_3;
GUIC *wifi_4;
GUIC *wifi_5;
GUIC *wifi_6;
GUIC *wifi_7;

// const char* format(double num, int prec) {
// std::stringstream stream;
// if( !isnanf(num) ) stream << std::fixed << std::setprecision(prec) << num;
// else stream << "No Fix";
// return stream.str().c_str();
// }

void reset(std::stringstream &str) {
  str.str(std::string());
  str.clear();
}

Window::Window(bool &err) { err = init(); }

Window::Window() { init(); }

Window::~Window() { destroy(); }

void Window::subscribe(ros::NodeHandle &nh) {
  connect_sub[0] =
      nh.subscribe("/bebop_1/wificonnection", 10, &Window::connect_1, this);
  connect_sub[1] =
      nh.subscribe("/bebop_2/wificonnection", 10, &Window::connect_2, this);
  connect_sub[2] =
      nh.subscribe("/bebop_3/wificonnection", 10, &Window::connect_3, this);
  connect_sub[3] =
      nh.subscribe("/bebop_4/wificonnection", 10, &Window::connect_4, this);
  connect_sub[4] =
      nh.subscribe("/bebop_5/wificonnection", 10, &Window::connect_5, this);
  connect_sub[5] =
      nh.subscribe("/bebop_6/wificonnection", 10, &Window::connect_6, this);
  connect_sub[6] =
      nh.subscribe("/bebop_7/wificonnection", 10, &Window::connect_7, this);

  wifi_alive_sub[0] = nh.subscribe("/bebop_1/wifi_condition", 10,
                                   &Window::connect_count_1, this);
  wifi_alive_sub[1] = nh.subscribe("/bebop_2/wifi_condition", 10,
                                   &Window::connect_count_2, this);
  wifi_alive_sub[2] = nh.subscribe("/bebop_3/wifi_condition", 10,
                                   &Window::connect_count_3, this);
  wifi_alive_sub[3] = nh.subscribe("/bebop_4/wifi_condition", 10,
                                   &Window::connect_count_4, this);
  wifi_alive_sub[4] = nh.subscribe("/bebop_5/wifi_condition", 10,
                                   &Window::connect_count_5, this);
  wifi_alive_sub[5] = nh.subscribe("/bebop_6/wifi_condition", 10,
                                   &Window::connect_count_6, this);
  wifi_alive_sub[6] = nh.subscribe("/bebop_7/wifi_condition", 10,
                                   &Window::connect_count_7, this);

  time_sub[0] = nh.subscribe("/duration_time", 10, &Window::timeset, this);
  time_sub[1] = nh.subscribe("/current_time", 10, &Window::clocker, this);
}

void Window::event(SDL_Event *event) {
  if (!alive)
    return;

  if (event->type == SDL_QUIT) {
    alive = false;
  } else if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (drone_1->inside(event->button.x, event->button.y))
      drone_1->callCB();
    if (drone_2->inside(event->button.x, event->button.y))
      drone_2->callCB();
    if (drone_3->inside(event->button.x, event->button.y))
      drone_3->callCB();
    if (drone_4->inside(event->button.x, event->button.y))
      drone_4->callCB();
    if (drone_5->inside(event->button.x, event->button.y))
      drone_5->callCB();
    if (drone_6->inside(event->button.x, event->button.y))
      drone_6->callCB();
    if (drone_7->inside(event->button.x, event->button.y))
      drone_7->callCB();

    if (script_1->inside(event->button.x, event->button.y))
      script_1->callCB();
    if (script_2->inside(event->button.x, event->button.y))
      script_2->callCB();
    if (script_3->inside(event->button.x, event->button.y))
      script_3->callCB();

    if (start->inside(event->button.x, event->button.y))
      start->callCB();
    if (stop->inside(event->button.x, event->button.y))
      stop->callCB();
  }
}

void Window::update() {
  // do update
  if (!ok())
    return;

  if (connected_1) {
    if (connection_tmp_1 != connection_number_1) {
      tmp_1 = 0;
      connection_tmp_1 = connection_number_1;
    } else {
      if (tmp_1 > 100) {
        tmp_1 = 0;
        drone_1->setBG(100, 0, 0);
        drone_1->setText("    Disconnected...   ", ren, 0);
        connected_1 = false;
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_1 &");
      } else {
        drone_1->setBG(0, 100, 0);
        drone_1->setText("  Drone_1 Connected.  ", ren);
        tmp_1++;
      }
    }
  } else {
    if (drone_1->getText()[5] == 'C') {
      tmp_1++;
      if (tmp_1 > 100) {
        tmp_1 = 0;
        drone_1->setBG(100, 0, 0);
        drone_1->setText("    Disconnected...   ", ren, 0);
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_1 &");
      }
    }
  }

  if (connected_2) {
    if (connection_tmp_2 != connection_number_2) {
      tmp_2 = 0;
      connection_tmp_2 = connection_number_2;
    } else {
      if (tmp_2 > 100) {
        tmp_2 = 0;
        drone_2->setBG(100, 0, 0);
        drone_2->setText("    Disconnected...   ", ren, 0);
        connected_2 = false;
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_2 &");
      } else {
        drone_2->setBG(0, 100, 0);
        drone_2->setText("  Drone_2 Connected.  ", ren);
        tmp_2++;
      }
    }
  } else {
    if (drone_2->getText()[5] == 'C') {
      tmp_2++;
      if (tmp_2 > 100) {
        tmp_2 = 0;
        drone_2->setBG(100, 0, 0);
        drone_2->setText("    Disconnected...   ", ren, 0);
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_2 &");
      }
    }
  }

  if (connected_3) {
    if (connection_tmp_3 != connection_number_3) {
      tmp_3 = 0;
      connection_tmp_3 = connection_number_3;
    } else {
      if (tmp_3 > 100) {
        tmp_3 = 0;
        drone_3->setBG(100, 0, 0);
        drone_3->setText("    Disconnected...   ", ren, 0);
        connected_3 = false;
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_3 &");
      } else {
        drone_3->setBG(0, 100, 0);
        drone_3->setText("  Drone_3 Connected.  ", ren);
        tmp_3++;
      }
    }
  } else {
    if (drone_3->getText()[5] == 'C') {
      tmp_3++;
      if (tmp_3 > 100) {
        tmp_3 = 0;
        drone_3->setBG(100, 0, 0);
        drone_3->setText("    Disconnected...   ", ren, 0);
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_3 &");
      }
    }
  }

  if (connected_4) {
    if (connection_tmp_4 != connection_number_4) {
      tmp_4 = 0;
      connection_tmp_4 = connection_number_4;
    } else {
      if (tmp_4 > 100) {
        tmp_4 = 0;
        drone_4->setBG(100, 0, 0);
        drone_4->setText("    Disconnected...   ", ren, 0);
        connected_4 = false;
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_4 &");
      } else {
        drone_4->setBG(0, 100, 0);
        drone_4->setText("  Drone_4 Connected.  ", ren);
        tmp_4++;
      }
    }
  } else {
    if (drone_4->getText()[5] == 'C') {
      tmp_4++;
      if (tmp_4 > 100) {
        tmp_4 = 0;
        drone_4->setBG(100, 0, 0);
        drone_4->setText("    Disconnected...   ", ren, 0);
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_4 &");
      }
    }
  }

  if (connected_5) {
    if (connection_tmp_5 != connection_number_5) {
      tmp_5 = 0;
      connection_tmp_5 = connection_number_5;
    } else {
      if (tmp_5 > 100) {
        tmp_5 = 0;
        drone_5->setBG(100, 0, 0);
        drone_5->setText("    Disconnected...   ", ren, 0);
        connected_5 = false;
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_5 &");
      } else {
        drone_5->setBG(0, 100, 0);
        drone_5->setText("  Drone_5 Connected.  ", ren);
        tmp_5++;
      }
    }
  } else {
    if (drone_5->getText()[5] == 'C') {
      tmp_5++;
      if (tmp_5 > 100) {
        tmp_5 = 0;
        drone_5->setBG(100, 0, 0);
        drone_5->setText("    Disconnected...   ", ren, 0);
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_5 &");
      }
    }
  }

  if (connected_6) {
    if (connection_tmp_6 != connection_number_6) {
      tmp_6 = 0;
      connection_tmp_6 = connection_number_6;
    } else {
      if (tmp_6 > 100) {
        tmp_6 = 0;
        drone_6->setBG(100, 0, 0);
        drone_6->setText("    Disconnected...   ", ren, 0);
        connected_6 = false;
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_6 &");
      } else {
        drone_6->setBG(0, 100, 0);
        drone_6->setText("  Drone_6 Connected.  ", ren);
        tmp_6++;
      }
    }
  } else {
    if (drone_6->getText()[5] == 'C') {
      tmp_6++;
      if (tmp_6 > 100) {
        tmp_6 = 0;
        drone_6->setBG(100, 0, 0);
        drone_6->setText("    Disconnected...   ", ren, 0);
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_6 &");
      }
    }
  }

  if (connected_7) {
    if (connection_tmp_7 != connection_number_7) {
      tmp_7 = 0;
      connection_tmp_7 = connection_number_7;
    } else {
      if (tmp_7 > 100) {
        tmp_7 = 0;
        drone_7->setBG(100, 0, 0);
        drone_7->setText("    Disconnected...   ", ren, 0);
        connected_7 = false;
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_7 &");
      } else {
        drone_7->setBG(0, 100, 0);
        drone_7->setText("  Drone_7 Connected.  ", ren);
        tmp_7++;
      }
    }
  } else {
    if (drone_7->getText()[5] == 'C') {
      tmp_7++;
      if (tmp_7 > 100) {
        tmp_7 = 0;
        drone_7->setBG(100, 0, 0);
        drone_7->setText("    Disconnected...   ", ren, 0);
        system(
            "terminator --new-tab -H --execute killall bebop_driver_node_7 &");
      }
    }
  }

  // update
  std::stringstream str;
  str << "WiFi";
  wifi_title->setText(str.str(), ren);
  wifi_title->render(ren);

  reset(str);
  str << "|"
      << (abs(stat->getWifiStrength_1()) > 75
              ? "+      "
              : (abs(stat->getWifiStrength_1()) > 50
                     ? "+ +    "
                     : (abs(stat->getWifiStrength_1()) > 20 ? "+ + +  "
                                                            : "+ + + +")))
      << "|";
  wifi_1->setText(str.str(), ren);
  wifi_1->render(ren);

  reset(str);
  str << "|"
      << (abs(stat->getWifiStrength_2()) > 75
              ? "+      "
              : (abs(stat->getWifiStrength_2()) > 50
                     ? "+ +    "
                     : (abs(stat->getWifiStrength_2()) > 20 ? "+ + +  "
                                                            : "+ + + +")))
      << "|";
  wifi_2->setText(str.str(), ren);
  wifi_2->render(ren);

  reset(str);
  str << "|"
      << (abs(stat->getWifiStrength_3()) > 75
              ? "+      "
              : (abs(stat->getWifiStrength_3()) > 50
                     ? "+ +    "
                     : (abs(stat->getWifiStrength_3()) > 20 ? "+ + +  "
                                                            : "+ + + +")))
      << "|";
  wifi_3->setText(str.str(), ren);
  wifi_3->render(ren);

  reset(str);
  str << "|"
      << (abs(stat->getWifiStrength_4()) > 75
              ? "+      "
              : (abs(stat->getWifiStrength_4()) > 50
                     ? "+ +    "
                     : (abs(stat->getWifiStrength_4()) > 20 ? "+ + +  "
                                                            : "+ + + +")))
      << "|";
  wifi_4->setText(str.str(), ren);
  wifi_4->render(ren);

  reset(str);
  str << "|"
      << (abs(stat->getWifiStrength_5()) > 75
              ? "+      "
              : (abs(stat->getWifiStrength_5()) > 50
                     ? "+ +    "
                     : (abs(stat->getWifiStrength_5()) > 20 ? "+ + +  "
                                                            : "+ + + +")))
      << "|";
  wifi_5->setText(str.str(), ren);
  wifi_5->render(ren);

  reset(str);
  str << "|"
      << (abs(stat->getWifiStrength_6()) > 75
              ? "+      "
              : (abs(stat->getWifiStrength_6()) > 50
                     ? "+ +    "
                     : (abs(stat->getWifiStrength_6()) > 20 ? "+ + +  "
                                                            : "+ + + +")))
      << "|";
  wifi_6->setText(str.str(), ren);
  wifi_6->render(ren);

  reset(str);
  str << "|"
      << (abs(stat->getWifiStrength_7()) > 75
              ? "+      "
              : (abs(stat->getWifiStrength_7()) > 50
                     ? "+ +    "
                     : (abs(stat->getWifiStrength_7()) > 20 ? "+ + +  "
                                                            : "+ + + +")))
      << "|";
  wifi_7->setText(str.str(), ren);
  wifi_7->render(ren);

  reset(str);

  str << play_minute;
  if ((int(play_time) % 60 < 10))
    str << ":0" << std::fixed << std::setprecision(2)
        << play_time - play_minute * 60 << " / " << performance_minute;
  else
    str << ":" << std::fixed << std::setprecision(2)
        << play_time - play_minute * 60 << " / " << performance_minute;
  if ((int(performance_time) % 60 < 10))
    str << ":0" << performance_time - performance_minute * 60;
  else
    str << ":" << performance_time - performance_minute * 60;

  if (performance_minute == 0) {
    reset(str);
    str << "0:00 / 0:00";
  }

  watch->setText(str.str(), ren);
  watch->render(ren);

  reset(str);
  str << "BATTERY";
  batt_title->setText(str.str(), ren);
  batt_title->render(ren);

  reset(str);
  str << stat->getBattery_1() << "%";
  batt_1->setText(str.str(), ren);
  batt_1->render(ren);

  reset(str);
  str << stat->getBattery_2() << "%";
  batt_2->setText(str.str(), ren);
  batt_2->render(ren);

  reset(str);
  str << stat->getBattery_3() << "%";
  batt_3->setText(str.str(), ren);
  batt_3->render(ren);

  reset(str);
  str << stat->getBattery_4() << "%";
  batt_4->setText(str.str(), ren);
  batt_4->render(ren);

  reset(str);
  str << stat->getBattery_5() << "%";
  batt_5->setText(str.str(), ren);
  batt_5->render(ren);

  reset(str);
  str << stat->getBattery_6() << "%";
  batt_6->setText(str.str(), ren);
  batt_6->render(ren);

  reset(str);
  str << stat->getBattery_7() << "%";
  batt_7->setText(str.str(), ren);
  batt_7->render(ren);

  reset(str);
  str << "Scenario";
  script_title->setText(str.str(), ren);
  script_title->render(ren);

  drone_1->render(ren);
  drone_2->render(ren);
  drone_3->render(ren);
  drone_4->render(ren);
  drone_5->render(ren);
  drone_6->render(ren);
  drone_7->render(ren);

  script_1->render(ren);
  script_2->render(ren);
  script_3->render(ren);

  start->render(ren);
  stop->render(ren);

  // FUCK THIS THING. SOLID 3 hours GOOONNNNEEE because it was in the if
  SDL_RenderPresent(ren);
}

bool Window::ok() { return alive; }

void destGUI() {
  delete watch;
  delete batt_title;
  delete wifi_title;
  delete batt_1;
  delete batt_2;
  delete batt_3;
  delete batt_4;
  delete batt_5;
  delete batt_6;
  delete batt_7;
  delete wifi_1;
  delete wifi_2;
  delete wifi_3;
  delete wifi_4;
  delete wifi_5;
  delete wifi_6;
  delete wifi_7;
  delete script_title;
  delete window->drone_1;
  delete window->drone_2;
  delete window->drone_3;
  delete window->drone_4;
  delete window->drone_5;
  delete window->drone_6;
  delete window->drone_7;
  delete window->script_1;
  delete window->script_2;
  delete window->script_3;
  delete window->start;
  delete window->stop;
}

void Window::destroy() {
  alive = false;

  TTF_CloseFont(font);
  SDL_DestroyTexture(video);

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  destGUI();
  TTF_Quit();
  SDL_Quit();
}

void Window::makeGUI() {
  watch = new GUIC(font, 250, 420, -1, 24);
  std::stringstream str;
  str << "0.00 / 0.00";
  watch->setText(str.str(), ren);
  watch->render(ren);

  wifi_title = new GUIC(font, 470, 10, -1, 24);
  batt_title = new GUIC(font, 310, 10, -1, 24);

  wifi_1 = new GUIC(font, 445, 50, -1, 24);
  wifi_2 = new GUIC(font, 445, 100, -1, 24);
  wifi_3 = new GUIC(font, 445, 150, -1, 24);
  wifi_4 = new GUIC(font, 445, 200, -1, 24);
  wifi_5 = new GUIC(font, 445, 250, -1, 24);
  wifi_6 = new GUIC(font, 445, 300, -1, 24);
  wifi_7 = new GUIC(font, 445, 350, -1, 24);

  batt_1 = new GUIC(font, 333, 50, -1, 24);
  batt_2 = new GUIC(font, 333, 100, -1, 24);
  batt_3 = new GUIC(font, 333, 150, -1, 24);
  batt_4 = new GUIC(font, 333, 200, -1, 24);
  batt_5 = new GUIC(font, 333, 250, -1, 24);
  batt_6 = new GUIC(font, 333, 300, -1, 24);
  batt_7 = new GUIC(font, 333, 350, -1, 24);

  script_title = new GUIC(font, 650, 10, -1, 24);

  drone_1 = new GUIC(font, 50, 50, -1, 24);
  drone_1->setBG(100, 100, 100);
  drone_1->setText("    Drone_1 Launch    ", ren);
  drone_1->setCallback([this](GUIC *g) {
    if (g->getText()[4] == 'D') {
      g->setBG(170, 70, 70);
      g->setText("     Connecting...    ", ren, 0);
      system("terminator --new-tab -H --execute killall bebop_driver_node_1 &");
      system("terminator --new-tab -H --execute roslaunch bebop_driver "
             "bebop_node_1.launch &");
    } else {
    }
  });

  drone_2 = new GUIC(font, 50, 100, -1, 24);
  drone_2->setBG(100, 100, 100);
  drone_2->setText("    Drone_2 Launch    ", ren);
  drone_2->setCallback([this](GUIC *g) {
    if (g->getText()[4] == 'D') {
      g->setBG(170, 70, 70);
      g->setText("     Connecting...    ", ren, 0);
      system("terminator --new-tab -H --execute killall bebop_driver_node_2 &");
      system("terminator --new-tab -H --execute roslaunch bebop_driver "
             "bebop_node_2.launch &");
    } else {
    }
  });

  drone_3 = new GUIC(font, 50, 150, -1, 24);
  drone_3->setBG(100, 100, 100);
  drone_3->setText("    Drone_3 Launch    ", ren);
  drone_3->setCallback([this](GUIC *g) {
    if (g->getText()[4] == 'D') {
      g->setBG(170, 70, 70);
      g->setText("     Connecting...    ", ren, 0);
      system("terminator --new-tab -H --execute killall bebop_driver_node_3 &");
      system("terminator --new-tab -H --execute roslaunch bebop_driver "
             "bebop_node_3.launch &");
    } else {
    }
  });

  drone_4 = new GUIC(font, 50, 200, -1, 24);
  drone_4->setBG(100, 100, 100);
  drone_4->setText("    Drone_4 Launch    ", ren);
  drone_4->setCallback([this](GUIC *g) {
    if (g->getText()[4] == 'D') {
      g->setBG(170, 70, 70);
      g->setText("     Connecting...    ", ren, 0);
      system("terminator --new-tab -H --execute killall bebop_driver_node_4 &");
      system("terminator --new-tab -H --execute roslaunch bebop_driver "
             "bebop_node_4.launch &");
    } else {
    }
  });

  drone_5 = new GUIC(font, 50, 250, -1, 24);
  drone_5->setBG(100, 100, 100);
  drone_5->setText("    Drone_5 Launch    ", ren);
  drone_5->setCallback([this](GUIC *g) {
    if (g->getText()[4] == 'D') {
      g->setBG(170, 70, 70);
      g->setText("     Connecting...    ", ren, 0);
      system("terminator --new-tab -H --execute killall bebop_driver_node_5 &");
      system("terminator --new-tab -H --execute roslaunch bebop_driver "
             "bebop_node_5.launch &");
    } else {
    }
  });

  drone_6 = new GUIC(font, 50, 300, -1, 24);
  drone_6->setBG(100, 100, 100);
  drone_6->setText("    Drone_6 Launch    ", ren);
  drone_6->setCallback([this](GUIC *g) {
    if (g->getText()[4] == 'D') {
      g->setBG(170, 70, 70);
      g->setText("     Connecting...    ", ren, 0);
      system("terminator --new-tab -H --execute killall bebop_driver_node_6 &");
      system("terminator --new-tab -H --execute roslaunch bebop_driver "
             "bebop_node_6.launch &");
    } else {
    }
  });

  drone_7 = new GUIC(font, 50, 350, -1, 24);
  drone_7->setBG(100, 100, 100);
  drone_7->setText("    Drone_7 Launch    ", ren);
  drone_7->setCallback([this](GUIC *g) {
    if (g->getText()[4] == 'D') {
      g->setBG(170, 70, 70);
      g->setText("     Connecting...    ", ren, 0);
      system("terminator --new-tab -H --execute killall bebop_driver_node_7 &");
      system("terminator --new-tab -H --execute roslaunch bebop_driver "
             "bebop_node_7.launch &");
    } else {
    }
  });

  script_1 = new GUIC(font, 622, 120, -1, 24);
  script_1->setBG(100, 100, 100);
  script_1->setText("  Scenario 1  ", ren);
  script_1->setCallback([this](GUIC *g) {
    if (script_2->getText()[5] != 'O' && script_3->getText()[3] != 'O') {
      if (g->getText()[2] == 'S') {
        g->setBG(0, 100, 0);
        g->setText("     ON     ", ren, 0);
        system("terminator --new-tab -H --execute roslaunch bebop_command "
               "script_1.launch &");
      } else {
        g->setBG(100, 100, 100);
        g->setText("  Scenario 1  ", ren, 0);
        system("terminator --new-tab -H --execute killall script_1 &");
      }
    }
  });

  script_2 = new GUIC(font, 622, 200, -1, 24);
  script_2->setBG(100, 100, 100);
  script_2->setText("  Scenario 2  ", ren);
  script_2->setCallback([this](GUIC *g) {
    if (script_1->getText()[5] != 'O' && script_3->getText()[3] != 'O') {
      if (g->getText()[2] == 'S') {
        g->setBG(0, 100, 0);
        g->setText("     ON     ", ren, 0);
        system("terminator --new-tab -H --execute roslaunch bebop_command "
               "script_2.launch &");
      } else {
        g->setBG(100, 100, 100);
        g->setText("  Scenario 2  ", ren, 0);
        system("terminator --new-tab -H --execute killall script_2 &");
      }
    }
  });

  script_3 = new GUIC(font, 622, 280, -1, 24);
  script_3->setBG(100, 100, 100);
  script_3->setText("  Scenario 3  ", ren);
  script_3->setCallback([this](GUIC *g) {
    if (script_1->getText()[5] != 'O' && script_2->getText()[3] != 'O') {
      if (g->getText()[2] == 'S') {
        g->setBG(0, 100, 0);
        g->setText("     ON     ", ren, 0);
        system("terminator --new-tab -H --execute roslaunch bebop_command "
               "script_3.launch &");
      } else {
        g->setBG(100, 100, 100);
        g->setText("  Scenario 3  ", ren, 0);
        system("terminator --new-tab -H --execute killall script_3 &");
      }
    }
  });

  start = new GUIC(font, 500, 420, -1, 24);
  start->setBG(100, 100, 100);
  start->setText("   Start   ", ren);
  start->setCallback([this](GUIC *g) {
    if (click) {
      g->setBG(0, 100, 0);
      g->setText("   Start   ", ren);
      stop->setBG(100, 100, 100);
      stop->setText("   Stop   ", ren);
      system("terminator --new-tab -H --execute killall bebop_command &");
      system("terminator --new-tab -H --execute roslaunch bebop_command "
             "start.launch &");
      system("terminator --new-tab -H --execute roslaunch bebop_command "
             "stop.launch &");
      click = false;
    } else
      ;
  });

  stop = new GUIC(font, 645, 420, -1, 24);
  stop->setBG(100, 100, 100);
  stop->setText("   Stop   ", ren);
  stop->setCallback([this](GUIC *g) {
    if (!click) {
      g->setBG(100, 0, 0);
      g->setText("   Stop   ", ren);
      start->setBG(100, 100, 100);
      start->setText("   Start   ", ren);
      if (script_1->getText()[5] == 'O') {
        script_1->setBG(100, 100, 100);
        script_1->setText("  Scenario 1  ", ren, 0);
        system("terminator --new-tab -H --execute killall script_1 &");
      } else if (script_2->getText()[5] == 'O') {
        script_2->setBG(100, 100, 100);
        script_2->setText("  Scenario 2  ", ren, 0);
        system("terminator --new-tab -H --execute killall script_2 &");
      } else if (script_3->getText()[5] == 'O') {
        script_3->setBG(100, 100, 100);
        script_3->setText("  Scenario 3  ", ren, 0);
        system("terminator --new-tab -H --execute killall script_3 &");
      }
      system("terminator --new-tab -H --execute rostopic pub -1 /stop_it "
             "std_msgs/Bool 'data: true' &");
      performance_minute = 0;
      play_time = 0;
      click = true;
    } else
      ;
  });
}

bool Window::init() {
  alive = false;
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    ROS_ERROR("SDL INIT FAIL: %s\n", SDL_GetError());
    return true;
  }

  alive = true;
  if (TTF_Init() < 0) {
    ROS_ERROR("TTF INIT FAIL: %s\n", TTF_GetError());
    return true;
  }

  font = TTF_OpenFont(font_path.c_str(), 20);
  if (font == NULL)
    ROS_ERROR("TTF FONT LOAD FAIL: %s\n", TTF_GetError());

  // return true;
  SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL,
                              &win, &ren);
  if (win == NULL || ren == NULL) {
    ROS_ERROR("SDL CREATE WINDOW FAIL: %s\n", SDL_GetError());
    return true;
  }

  registerEventListener(this);
  SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
  SDL_RenderClear(ren);
  SDL_RenderPresent(ren);

  makeGUI();
  return false;
}

void Window::connect_1(const std_msgs::Bool::ConstPtr &msg) {
  connected_1 = msg->data;
}

void Window::connect_2(const std_msgs::Bool::ConstPtr &msg) {
  connected_2 = msg->data;
}

void Window::connect_3(const std_msgs::Bool::ConstPtr &msg) {
  connected_3 = msg->data;
}

void Window::connect_4(const std_msgs::Bool::ConstPtr &msg) {
  connected_4 = msg->data;
}

void Window::connect_5(const std_msgs::Bool::ConstPtr &msg) {
  connected_5 = msg->data;
}

void Window::connect_6(const std_msgs::Bool::ConstPtr &msg) {
  connected_6 = msg->data;
}

void Window::connect_7(const std_msgs::Bool::ConstPtr &msg) {
  connected_7 = msg->data;
}

void Window::connect_count_1(const std_msgs::UInt8::ConstPtr &msg) {
  connection_number_1 = msg->data;
}

void Window::connect_count_2(const std_msgs::UInt8::ConstPtr &msg) {
  connection_number_2 = msg->data;
}

void Window::connect_count_3(const std_msgs::UInt8::ConstPtr &msg) {
  connection_number_3 = msg->data;
}

void Window::connect_count_4(const std_msgs::UInt8::ConstPtr &msg) {
  connection_number_4 = msg->data;
}

void Window::connect_count_5(const std_msgs::UInt8::ConstPtr &msg) {
  connection_number_5 = msg->data;
}

void Window::connect_count_6(const std_msgs::UInt8::ConstPtr &msg) {
  connection_number_6 = msg->data;
}

void Window::connect_count_7(const std_msgs::UInt8::ConstPtr &msg) {
  connection_number_7 = msg->data;
}

void Window::timeset(const std_msgs::Float32::ConstPtr &msg) {
  performance_time = msg->data;
  performance_minute = performance_time / 60;
}

void Window::clocker(const std_msgs::UInt32::ConstPtr &msg) {
  play_time = msg->data / 100.0;
  play_minute = play_time / 60;
}
