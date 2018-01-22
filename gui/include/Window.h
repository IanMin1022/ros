#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Events.h"
#include "GUI.h"
#include <SDL2/SDL.h>
#include <sensor_msgs/Image.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt32.h>
#include <std_msgs/UInt8.h>
#include <ros/ros.h>

class Window : Listener {
public:
	Window(bool&);
	Window(void);
	~Window(void) noexcept;
	Window(const Window& other) = delete;
	Window(Window && other) = delete;
	void event(SDL_Event*);
	void update(void);
	void destroy(void);
	bool ok(void);
	void makeGUI(void);

	void subscribe(ros::NodeHandle&);

	void connect_1(const std_msgs::Bool::ConstPtr&);
	void connect_2(const std_msgs::Bool::ConstPtr&);
	void connect_3(const std_msgs::Bool::ConstPtr&);
	void connect_4(const std_msgs::Bool::ConstPtr&);
	void connect_5(const std_msgs::Bool::ConstPtr&);
	void connect_6(const std_msgs::Bool::ConstPtr&);
	void connect_7(const std_msgs::Bool::ConstPtr&);

	void connect_count_1(const std_msgs::UInt8::ConstPtr&);
	void connect_count_2(const std_msgs::UInt8::ConstPtr&);
	void connect_count_3(const std_msgs::UInt8::ConstPtr&);
	void connect_count_4(const std_msgs::UInt8::ConstPtr&);
	void connect_count_5(const std_msgs::UInt8::ConstPtr&);
	void connect_count_6(const std_msgs::UInt8::ConstPtr&);
	void connect_count_7(const std_msgs::UInt8::ConstPtr&);

	void updateVideoTexture(const sensor_msgs::ImageConstPtr&);

	void timeset(const std_msgs::Float32::ConstPtr&);
	void clocker(const std_msgs::UInt32::ConstPtr&);

	void initCircle(int);

	static std::string font_path;
	static std::string circle_path;
	bool connected_1 = false, connected_2 = false, connected_3 = false, connected_4 = false, connected_5 = false, connected_6 = false, connected_7 = false;
	int connection_number_1 = 0, connection_number_2 = 0, connection_number_3 = 0, connection_number_4 = 0, connection_number_5 = 0, connection_number_6 = 0, connection_number_7 = 0;
	int connection_tmp_1 = 0, connection_tmp_2 = 0, connection_tmp_3 = 0, connection_tmp_4 = 0, connection_tmp_5 = 0, connection_tmp_6 = 0, connection_tmp_7 = 0;
	int tmp_1 = 0, tmp_2 = 0, tmp_3 = 0, tmp_4 = 0, tmp_5 = 0, tmp_6 = 0, tmp_7 = 0;
	GUIC* drone_1;
	GUIC* drone_2;
	GUIC* drone_3;
	GUIC* drone_4;
	GUIC* drone_5;
	GUIC* drone_6;
	GUIC* drone_7;

	GUIC* script_1;
	GUIC* script_2;
	GUIC* script_3;

	GUIC* start;
	GUIC* stop;

	bool click = true;

private:
	SDL_Window* win = NULL;
	SDL_Renderer* ren = NULL;
	SDL_Texture* video = NULL;
	SDL_Texture* circle = NULL;
	sensor_msgs::Image image;
	TTF_Font* font = NULL;
	bool video_dirty = false;
	bool alive = false;
	bool init(void);
	double performance_time = 0, play_time = 0;
	int performance_minute = 0, play_minute = 0;

	ros::Subscriber connect_sub[7];
	ros::Subscriber wifi_alive_sub[7];
	ros::Subscriber time_sub[2];

	// Window(const Window&);
};

extern Window* window;

#endif
