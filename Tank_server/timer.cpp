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

timer_::timer_()
{
	//计数器频率
	QueryPerformanceFrequency(&frequence);
	started = false;
}

void timer_::start()
{
	//获取开始时计数器显示数字
	QueryPerformanceCounter(&start_time);
	started = true;
}

double timer_::stop()
		{
			if (!started)return 0.0;
			LARGE_INTEGER end_time;
			//获取结束时计数器显示数字
			QueryPerformanceCounter(&end_time);
			started = false;
			//计算时间
			return (double)(end_time.QuadPart - start_time.QuadPart) / frequence.QuadPart;
		}
