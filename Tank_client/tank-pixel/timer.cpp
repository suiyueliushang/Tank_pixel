#include "timer.h"

/*
author: K024
*/
float my_clock()
{
	LARGE_INTEGER c, f;
	QueryPerformanceCounter(&c);
	QueryPerformanceFrequency(&f);
	return (float)c.QuadPart / f.QuadPart;
}
