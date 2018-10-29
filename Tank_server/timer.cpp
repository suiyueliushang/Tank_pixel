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
	//������Ƶ��
	QueryPerformanceFrequency(&frequence);
	started = false;
}

void timer_::start()
{
	//��ȡ��ʼʱ��������ʾ����
	QueryPerformanceCounter(&start_time);
	started = true;
}

double timer_::stop()
		{
			if (!started)return 0.0;
			LARGE_INTEGER end_time;
			//��ȡ����ʱ��������ʾ����
			QueryPerformanceCounter(&end_time);
			started = false;
			//����ʱ��
			return (double)(end_time.QuadPart - start_time.QuadPart) / frequence.QuadPart;
		}
