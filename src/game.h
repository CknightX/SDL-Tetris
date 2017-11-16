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


	int score; //����
	int speed=300; //�ٶ��趨
	int delay = speed - 50; //�ӳ��趨
	Map map;
	Window window;
};
#endif