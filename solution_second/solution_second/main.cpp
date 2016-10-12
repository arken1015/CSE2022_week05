#include <iostream>

template <typename T>
class Vector2D
{
public:
	T x_;
	T y_;

	Vector2D(T x, T y)
	{
		x_ = x;
		y_ = y;
	}

	Vector2D()
	{
		x_ = (int)0;
		y_ = (int)0;
	}

	void print()
	{
		std::cout << "X value is " << x_ << "\nY value is " << y_ << std::endl;
	}
};

int main()
{
	Vector2D<int> _int2D(10, 20);
	Vector2D<float> _float2D(10.5f, 21.5f);
	Vector2D<double> _double2D(21.13579f, 33.142563441f);

	_int2D.print();
	_float2D.print();
	_double2D.print();
}