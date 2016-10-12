#include <glfw3.h>
#include <cstring>
#include <stdlib.h>		  // srand, rand
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <math.h>
#include <vector>

float* pixels;
int __width = 800;
int __height = 600;

class Box // NO PARENT
{
public:
	int _x0;
	int _x1;
	int _y0;
	int _y1;
	float _red;
	float _green;
	float _blue;
	// some variables

	Box(const int& x0, const int& x1, const int& y0, const int& y1, const float& red, const float& green, const float& blue)
	{
		_x0 = x0;
		_x1 = x1;
		_y0 = y0;
		_y1 = y1;
		_red = red;
		_green = green;
		_blue = blue;
	}
	Box()
	{
		_x0 = 10;
		_x1 = 20;
		_y0 = 10;
		_y1 = 20;
		_red = 0.0f;
		_green = 0.0f;
		_blue = 0.0f;
	}
	void draw()
	{
		for (int x = _x0; x <= _x1; x++)
			{
				drawPixel(x, this->_y0, this->_red, this->_green, this->_blue);
				drawPixel(x, this->_y1, this->_red, this->_green, this->_blue);
			}

			for (int y = _y0; y <= _y1; y++)
			{
				drawPixel(this->_x0, y, this->_red, this->_green, this->_blue);
				drawPixel(this->_x1, y, this->_red, this->_green, this->_blue);
			}
		}
	void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
	{
		pixels[(i + __width * j) * 3 + 0] = red;
		pixels[(i + __width * j) * 3 + 1] = green;
		pixels[(i + __width * j) * 3 + 2] = blue;
	}
};

class Circle // NO PARENT
{

public:
	int _x;
	int _y;
	int _r;
	float _red;
	float _green;
	float _blue;
	// some variables

	Circle(const int& x, const int& y, const int& r, const float& red, const float& green, const float& blue)
	{
		_x = x;
		_y = y;
		_r = r;
		_red = red;
		_green = green;
		_blue = blue;
	}
	Circle()
	{
		_x = 200;
		_y = 200;
		_r = 10;
		_red = 0.0f;
		_green = 0.0f;
		_blue = 0.0f;
	}
	void draw()
	{
		float r_square = _r * _r;

		for (int i = -_r; i <= 0; i++)
		{
			drawPixel(i + _x, sqrt(r_square - i*i) + _y, _red, _green, _blue);
			drawPixel(i + _x, -1 * sqrt(r_square - i*i) + _y, _red, _green, _blue);
			drawPixel(sqrt(r_square - i *i) + _x, i + _y, _red, _green, _blue);
			drawPixel(-1 * sqrt(r_square - i *i) + _x, i + _y, _red, _green, _blue);
		}

		for (int i = _r; i >= 0; i--)
		{
			drawPixel(i + _x, sqrt(r_square - i*i) + _y, _red, _green, _blue);
			drawPixel(i + _x, -1 * sqrt(r_square - i*i) + _y, _red, _green, _blue);
			drawPixel(sqrt(r_square - i *i) + _x, i + _y, _red, _green, _blue);
			drawPixel(-1 * sqrt(r_square - i *i) + _x, i + _y, _red, _green, _blue);
		}
	}
	void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
	{
		pixels[(i + __width * j) * 3 + 0] = red;
		pixels[(i + __width * j) * 3 + 1] = green;
		pixels[(i + __width * j) * 3 + 2] = blue;
	}
};

template <class C>
class GeometricObject : GeometricObjectInterface
{
public:
	GeometricObject()
	{
		return new C;
	}

	// implement here
};

class GeometricObjectInterface
{
public:
	GeometricObjectInterface()
	{

	}
	virtual void draw()
	{

	}

	// implement here
};

Box box(10, 20, 10, 20, 0.0f, 0.0f, 0.0f);

class Window
{
private:
	int _width = 800;
	int _height = 600;
	int _delay = 100;
	std::vector<GeometricObjectInterface*> obj_list;

public:
	GLFWwindow* window;

	Window(const int width, const int height)
	{
		_width = width;
		_height = height;
		pixels = new float[width*height * 3];
		if (!glfwInit())
			exit(-1);

		window = glfwCreateWindow(_width, _height, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit(-1);
		}

		glfwMakeContextCurrent(window);
		glClearColor(1, 1, 1, 1);

		//obj_list.push_back(new GeometricObject<Box>);
		//obj_list.push_back(new GeometricObject<Circle>);
	}

	~Window()
	{
		delete[] pixels;
	}

	void setDelay(const int delay)
	{
		_delay = delay;
	}

	void print()
	{
		box.draw();

		for (auto itr : obj_list)itr->draw();
	}
};

// And implement an templatized GeometricObject class.
int main()
{
	Window window(800, 600);
	window.setDelay(100);

	while (!glfwWindowShouldClose(window.window))
	{
		window.print();
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}

	glfwTerminate();

	window.~Window();

	return 0;
}
