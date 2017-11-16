#include "map.h"
Map::Map(int width, int height) :width(width), height(height), cube(height, width) {} //地图大小
Pos Map::get_size()const { return std::make_pair(width*block_width, height*block_width); }
void Map::set_block(std::shared_ptr<Block> block)
{
	curr = block;
}
bool Map::runstep()
{
	if (curr == nullptr)
		return false;
	auto bak = *curr;
	curr->move(direction::down);
	if (!is_legal()) //落地
	{
		for (auto &i : bak.get_shape()) //落地且顶部到达屏幕,游戏结束
		{
			if (i.second <= 0)
			{
				is_gameover = true;
				return false;
			}
		}
		add_block(bak);
		remove_line(bak); //消行
		return false;
	}
	return true;

}
void Map::remove_line(const Block& block)
{
	auto shape = block.get_shape();
	vector<int> lines;
	for (auto &i : shape) //保存所有y坐标
		lines.push_back(i.second);
	std::sort(lines.begin(), lines.end(), std::less<int>()); //从高处开始消除

	for (auto line : lines)
	{
		bool is_remove = true;
		for (int i = 0; i < width; ++i)
		{
			bool value = cube.at(i, line);
			if (value == false)
			{
				is_remove = false;
				break;
			}
		}
		if (is_remove)
		{
			cube.down(line);
		}
	}

}
bool Map::_is_legal(const Pos& p)const //当前位置是否合法(碰撞检测)
{
	if (p.first < 0 || p.first + 1 > width)
		return false;
	if (p.second + 1 > height)
		return false;
	if (p.second < 0)
		return true;
	if (cube.at(p.first, p.second))
		return false;
	return true;
}
bool Map::is_legal()const
{
	for (auto &i : curr->get_shape())
	{
		if (!_is_legal(i))
			return false;
	}
	return true;
}
void Map::add_block(const Block& block)
{
	for (auto &i : block.get_shape())
		add_cube(i);
}
void Map::add_cube(const Pos& p)
{
	cube.set(p.first, p.second, true);
}
