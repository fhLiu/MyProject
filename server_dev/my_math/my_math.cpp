#include "my_math.h"
#include <iostream>

using namespace std;

int add_x(int x, int y)
{
	return x + y;
}

int sub_x(int x, int y)
{
	return x - y;
}

void swap_x(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void access_invalid_addr()
{
	int arr[10] = {0};
	arr[10] = 965;
	cout<<"10th is : "<<arr[10]<<endl;
}

void access_invalid_point()
{
	int * pi = new int(1);
	cout<<"pi is "<<*pi<<endl;
	delete pi;
	pi = nullptr;

	*pi = 20;
}

void leak_dynamic_mem()
{
	int* pi = new int[10];
	pi[0] = 10;
}

void mem_init_check()
{
	int arr[5];
	arr[0] = arr[1] = arr[3] = arr[4] = 0;
	int sum = 0;

	for (int i = 0; i < 5; ++i)
	{
		sum += arr[i];
	}

	if (sum == 33)
	{
		cout<<"sum is 33"<<endl;
	}else
	{
		cout<<"sum is "<<sum<<endl;
	}
	return;
}

void handle_math_func()
{
	int a = 15;
	int b = 12;
	cout<<"add result : "<<add_x(a, b)<<endl;
	cout<<"sub result : "<<sub_x(a, b)<<endl;

	// while(true)
	// {
	// 	a = 16;
	// 	b = 19;
	// 	swap_x(a, b);
	// }
	// access_invalid_addr();
	// leak_dynamic_mem();
	// mem_init_check();
	// access_invalid_point();
}