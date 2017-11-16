#include "block.h"

constexpr Pos shape_list[28] = {
	{0,0},{1,0},{0,-1},{-1,0}, //W
	{0,0},{0,1},{0,-1},{0,2}, //I
	{0,0},{0,-1},{0,1},{1,1}, //L
	{0,0},{1,0},{0,-1},{-1,-1},  //Z
	{0,0},{0,-1},{-1,0},{-1,-1},  //O
	{0,0},{-1,0},{0,-1},{1,-1},  //_Z
	{0,0},{0,-1},{0,1},{-1,1}, //_L
};

constexpr int init_ypos[7] = { -1,-2,-2,-1,-1,-1,-2 };


constexpr Pos move_direct[4] = {
	{-1,0},{1,0},{0,1},{0,0}
};

Block::Block(block_type type) :type(type)
{
	set_shape(type);
	relative_pos = { 5,init_ypos[static_cast<int>(type)] };
}
void Block::rotate(pair<double, double> spin)
{
	if (type == block_type::O)
		spin = { 0,0 };
	if (type == block_type::I)
		spin = { 1,1 };
	auto rotate_pos = [&spin](Pos& p) {
		double x, y;
		x = 0.5 + p.first + (0 - spin.first);
		y = 0.5 + p.second + (0 - spin.second);
		auto tmp = x;
		x = -y;
		y = tmp;
		x -= (0 - spin.first);
		y -= (0 - spin.second);
		p.first = (int)(x - 0.5);
		p.second = (int)(y - 0.5);
	};
	for (auto& i : shape)
	{
		rotate_pos(i);
	}

}

void Block::move(direction direct )
{
	/*
	auto idirect = move_direct[static_cast<int>(direct)];
	std::for_each(shape.begin(), shape.end(), [&idirect](Pos& p) {
	p.first += idirect.first;
	p.second += idirect.second;
	});
	*/
	auto idirect = move_direct[static_cast<int>(direct)];
	relative_pos.first += idirect.first;
	relative_pos.second += idirect.second;
}
void Block::set_relative(const Pos& pos) 
{
	relative_pos = pos; 
}
Shape Block::get_shape()const
{
	Shape tmp = shape;
	for (auto &i : tmp)
	{
		i.first += relative_pos.first;
		i.second += relative_pos.second;
	}
	return tmp;

}

void Block::set_shape(block_type type)
{
	int index = static_cast<int>(type);
	for (int i = 0; i < 4; ++i)
		shape[i] = shape_list[index * 4 + i];
}
