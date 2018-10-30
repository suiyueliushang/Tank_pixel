

#ifndef _TIMER_H_
#define _TIMER_H_

#include<Windows.h>

class timer_
{
public:

	//构造函数
	timer_();

	//开始计时
	void start();

	double stop();

private:
	LARGE_INTEGER frequence;
	LARGE_INTEGER start_time;
	bool started;
};

//浮点时钟，请使用差值
float my_clock();


#endif // !_TIMER_H_
