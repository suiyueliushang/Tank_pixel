

#ifndef _TIMER_H_
#define _TIMER_H_

#include<Windows.h>

class timer_
{
public:

	//���캯��
	timer_();

	//��ʼ��ʱ
	void start();

	double stop();

private:
	LARGE_INTEGER frequence;
	LARGE_INTEGER start_time;
	bool started;
};

//����ʱ�ӣ���ʹ�ò�ֵ
float my_clock();


#endif // !_TIMER_H_
