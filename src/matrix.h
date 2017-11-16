#ifndef _MATRIX_H
#define _MATRIX_H
#include<iostream>
template<typename T>
class Matrix
{
public:
	explicit Matrix(int x, int y) :x(x), y(y)
	{
		_init();
	}
	const T& at(int p_x, int p_y)const
	{
		return static_cast<const T&>(matrix[p_y][p_x]);
	}
	T& at(int p_x, int p_y)
	{
		return matrix[p_y][p_x];
	}
	void set(int p_x, int p_y, const T& value)
	{
		if (p_x >= y || p_y >= x)
			throw;
		matrix[p_y][p_x] = value;
	}
	void down(int line)  //将line行以上向下平移一行
	{
		for (int i = line; i > 0; --i)
		{
			for (int j = 0; j < y; ++j)
			{
				set(j, i, at(j, i-1));
			}
		}
		for (int i = 0; i < y; ++i)  
			set(0, i, T());
	}
	void print()
	{
		for (int i = 0; i < x; ++i)
		{
			for (int j = 0; j < y; ++j)
			{
				std::cout << at(i, j) << ' ';
			}
			std::cout << std::endl;
		}
	}
	~Matrix()
	{
		for (int i = 0; i < x; ++i)
			delete[]matrix[i];
		delete[]matrix;
	}
private:
	void _init()
	{
		matrix = new T*[x];
		for (int i = 0; i < x; ++i)
		{
			matrix[i] = new T[y];
			for (int j = 0; j < y; ++j)
				matrix[i][j] = T();
		}
	}
	int x, y;
	T** matrix;
};
#endif
