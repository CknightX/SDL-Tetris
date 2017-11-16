#ifndef _GAME_H
#define _GAME_H
#include "window.h"
#include<random>

class Game
{
public:
	Game(int width, int height);
	void set_speed(int speed);
	void set_delay(int delay);
	void run();
	void stop();
	void restart();
private:
	int random();


	int score; //分数
	int speed=300; //速度设定
	int delay = speed - 50; //延迟设定
	Map map;
	Window window;
};
#endif