#include "game.h"

Game::Game(int width , int height ) :map(width, height), window(width, height) {}
void Game::set_speed(int speed) { speed *= 100; if (speed > 900)speed = 900; this->speed = 950 - speed; }
void Game::set_delay(int delay) { this->delay = delay; }
void Game::run()
{
	bool quit = false;
	SDL_Event event;

	int sum = 0;
	direction direct = direction::down;
	map.set_block(std::make_shared<Block>(static_cast<block_type>(random()))); //设定初始方块
	while (!quit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			else if (event.type == SDL_KEYDOWN)
			{
				sum = delay; //延迟时间，方块在互相接触后可以继续调整的时间
				auto key = event.key.keysym.sym;
				auto bak = *map.curr;
				if (key == SDLK_LEFT)
				{
					map.curr->move(direction::left);
					if (!map.is_legal())
						*map.curr = bak;
					window.draw_map(map);
				}
				else if (key == SDLK_RIGHT)
				{
					map.curr->move(direction::right);
					if (!map.is_legal())
						*map.curr = bak;
					window.draw_map(map);
				}
				else if (key == SDLK_UP)
				{
					map.curr->rotate();
					if (!map.is_legal())
						*map.curr = bak;
					window.draw_map(map);
				}
				else if (key == SDLK_DOWN)
				{
					while (map.is_legal())
					{
						bak = *map.curr;
						map.curr->move(direction::down);
					}
					*map.curr = bak;
					window.draw_map(map);
				}
			}
		}
		SDL_Delay(5);
		sum = (sum + 5) % speed;
		if (sum == 0)
		{
			if (!map.runstep())
			{
				if (map.is_gameover)
				{
					quit = true;
					break;
				}
				map.set_block(std::make_shared<Block>(static_cast<block_type>(random())));
			}
			window.draw_map(map);
		}
	}
}
void Game::stop()
{

}
void Game::restart()
{

}
int Game::random()
{
	std::random_device rd; //种子
	std::mt19937 mt(rd()); //引擎
	return mt() % 7;
}

