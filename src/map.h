#ifndef _MAP_H
#define _MAP_H
#include "block.h"
#include "matrix.h"
#include<vector>
#include<memory>
using std::vector;
using std::shared_ptr;
class Map
{
	friend class Game;
	friend class Window;
public:
	Map(int width, int height);
	Pos get_size()const;
	void set_block(std::shared_ptr<Block> block);
	bool runstep();
	void remove_line(const Block& block);
	bool is_legal()const;
private:
	bool _is_legal(const Pos& p)const;
	void add_block(const Block& block);
	void add_cube(const Pos& p);
private:
	int width, height;
	static const size_t block_width = 40; //一个格子的宽度
	shared_ptr<Block> curr = nullptr;
	bool is_gameover = false;
	Matrix<bool> cube;

};
#endif