#include "window.h"

Window::Window(int width, int height)
{

	{
		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, width * Map::block_width, height * Map::block_width, SDL_WINDOW_SHOWN);
		render = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		square_surface = SDL_LoadBMP("res/square.bmp");
		square = SDL_CreateTextureFromSurface(render, square_surface);
		bg_surface = SDL_LoadBMP("res/bg1.bmp");
		bg = SDL_CreateTextureFromSurface(render, bg_surface);
	}
}

Window::~Window()
{
	SDL_FreeSurface(square_surface);
	SDL_DestroyTexture(square);
	SDL_DestroyRenderer(render);
	SDL_DestroyWindow(window);
}
void Window::draw_map(const Map& map)
{
	SDL_RenderClear(render);
	SDL_RenderCopy(render, bg, NULL, NULL);
	draw_line(map);
	for (int i = 0; i < map.width; ++i)
	{
		for (int j = 0; j < map.height; ++j)
		{
			if (map.cube.at(i, j))
				draw_cube({ i,j });
		}
	}
	if (map.curr.get() != nullptr)
		draw_block(*map.curr);
	SDL_RenderPresent(render);
}
void Window::draw_line(const Map& map)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	for (int i = 0; i < map.width; ++i)
	{
		SDL_RenderDrawLine(render, i*map.block_width, 0, i*map.block_width, map.block_width*map.height);
	}
	for (int i = 0; i < map.height; ++i)
	{
		SDL_RenderDrawLine(render, 0, i*map.block_width, map.width*map.block_width, i*map.block_width);
	}
	SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
}
void Window::draw_cube(const Pos& pos)
{
	SDL_Rect rect;
	rect.x = static_cast<int>(pos.first*Map::block_width);
	rect.y = static_cast<int>(pos.second*Map::block_width);
	rect.w = Map::block_width;
	rect.h = Map::block_width;
	SDL_RenderCopy(render, square, NULL, &rect);
}
void Window::draw_block(const Block& block)
{
	auto shape = block.get_shape();
	std::for_each(shape.begin(), shape.end(), [&](const Pos& p) {
		draw_cube(p);
	});
}


