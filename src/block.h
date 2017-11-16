#ifndef _BLOCK_H
#define _BLOCK_H
#include<array>
#include<utility>
using std::array;
using std::pair;

using Pos = pair<int, int>;
using Shape = array<Pos, 4>;

enum class block_type { W, I, L, Z, O,_Z, _L };
enum class direction{left,right,down,none};



class Block
{
public:
	explicit Block(block_type type);
	void rotate(pair<double, double> spin = { 0.5,0.5 });
	void move(direction direct = direction::down);
	void set_relative(const Pos& pos);
	Shape get_shape()const;

private:
	Shape shape;
	block_type type;
	Pos relative_pos ; //相对屏幕的位置

	void set_shape(block_type type);

};
#endif