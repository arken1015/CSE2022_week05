#include <iostream>
#include <string>

template <typename T>
//Defines typename template T
void print(void& i)
{
	std::cout << i << std::endl;
}
//Generic Function

int main()
{
	print<int>(1);
	print<float>(2.345f);
	print<std::string>("Hello World");

	return 0;
}