#ifndef _TIMER_H_
#define _TIMER_H_

#include<Windows.h>

class timer_
{
public:

	//构造函数
	timer_()
	{
		//计数器频率
		QueryPerformanceFrequency(&frequence);
		started = false;
	}

	//开始计时
	void start()
	{
		//获取开始时计数器显示数字
		QueryPerformanceCounter(&start_time);
		started = true;
	}
	double stop()
	{
		if (!started)return 0.0;
		LARGE_INTEGER end_time;
		//获取结束时计数器显示数字
		QueryPerformanceCounter(&end_time);
		started = false;
		//计算时间
		return (double)(end_time.QuadPart - start_time.QuadPart) / frequence.QuadPart;
	}

private:
	LARGE_INTEGER frequence;
	LARGE_INTEGER start_time;
	bool started;
};

//浮点时钟，请使用差值
float my_clock();


#endif // !_TIMER_H_
