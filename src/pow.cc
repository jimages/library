/*
 * Author: jiamges (jimages123@gmail.com)
 * Date: June 21 2018
 */
#include <cmath>
#include <iostream>

long long getPower(long long x, double base)
{
	if (base < 0)
		return 0;
	decltype(x) re = 1;
	for (int i = 0; i < base; ++i)
		re *= x;
	return re;
}

double getPower(double x, double base)
{	
	if (base < 0)
		return 0;
	decltype(x) re = 1;
	for (int i = 0; i < base; ++i)
		re *= x;
	return re;
}

