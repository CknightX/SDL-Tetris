#ifndef _WINDOW_H	
#define _WINDOW_H	
#include "SDL.h"
#include "map.h"
#include<algorithm>
class Window
{
public:
	Window(int width, int height);
	~Window();
	
	void draw_map(const Map& map);
	void draw_line(const Map& map);
private:
	void draw_cube(const Pos& pos);
	void draw_block(const Block& block);
private:
	SDL_Surface* square_surface = nullptr;
	SDL_Texture* square = nullptr;
	SDL_Surface* bg_surface = nullptr;
	SDL_Texture* bg = nullptr;
	SDL_Window* window = nullptr;
	SDL_Renderer* render = nullptr;
};
#endif
