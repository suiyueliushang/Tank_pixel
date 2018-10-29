#ifndef _TIMER_H_
#define _TIMER_H_

#include<Windows.h>

class timer_
{
public:

	//���캯��
	timer_()
	{
		//������Ƶ��
		QueryPerformanceFrequency(&frequence);
		started = false;
	}

	//��ʼ��ʱ
	void start()
	{
		//��ȡ��ʼʱ��������ʾ����
		QueryPerformanceCounter(&start_time);
		started = true;
	}
	double stop()
	{
		if (!started)return 0.0;
		LARGE_INTEGER end_time;
		//��ȡ����ʱ��������ʾ����
		QueryPerformanceCounter(&end_time);
		started = false;
		//����ʱ��
		return (double)(end_time.QuadPart - start_time.QuadPart) / frequence.QuadPart;
	}

private:
	LARGE_INTEGER frequence;
	LARGE_INTEGER start_time;
	bool started;
};

//����ʱ�ӣ���ʹ�ò�ֵ
float my_clock();


#endif // !_TIMER_H_
