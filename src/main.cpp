#include "game.h"
#include<iostream>
#include <functional>
int main(int argc, char** argv)
{
	Game a(10,20);
	a.set_speed(7); // 1-9
	a.run();
	return 0;
}