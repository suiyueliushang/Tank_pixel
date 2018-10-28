#ifndef _TANK_H_
#define _TANK_H_

#include <cmath>
#include "coordinate.h"
#include "item.h"
#include"input.h"



class tank
{
public:
	tank();
	~tank();

	enum tank_type
	{
		light,//����̹��
		medium,//����̹��
		heavy//����̹��
	};

	void enable(position, rotation, tank_type);
	bool isEnable();

	bool isDead();

	/*
	���º���
	ÿһ֡����
	����̹�˸���״̬
	*/
	//void update(float);

	void update(int, float, raw_input[]);
	void update(float);

	/*
	����̹���ƶ�״̬
	*/
	void set_uad(int);

	/*
	����̹����ת״̬
	*/
	void set_lar(int);

	position getPosition()const;
	rotation getRotation()const;
	rotation getCannon()const;

	/*
	��Ⱦ
	ÿ֡����
	���յ�ǰλ�ú���ת�ǽ�̹����Ⱦ����Ļ��
	int 0:�Լ�
	    1:����
	    2:�з�
	*/
	void render(int);

	/*
	̹�˷�����ײ���ص���һ֡λ�����ٶȹ���
	*/
	void onCollision();

	/*
	������׼��
	*/
	void set_aim(position);

	//��������ֵ
	void attacked(int);

	bool isCollideWith(tank&);

	bool isCollideWith(item&);

	//���ڣ�����װ��ʱ�䷵��true���������ӵ��ķ��䣩
	bool shoot();

	int type();

	//����ö����
	enum properties {
		life,
		load,
		max_speed,
		a_speed,
		rotate_speed,
		cannon_speed,
	};

	//��ȡ����
	float getProperty(properties);

	//��ȡ��N���ߵ�װ�׺��
	//0Ϊ����ʱ��
	float getArmor(int);

private:

	int m_status;
	tank_type m_type;

	float m_life;

	position m_position;//̹������λ��
	rotation m_rotation;//̹��������ת��
	rotation m_cannon_rotation=0;//��̨�����ת��

	float m_now_speed=0;//̹�������ٶ�

	int m_up_and_down=0;//̹���ƶ�״̬����ǰ����Ϊ1,������Ϊ-1,�޶���Ϊ0
	int m_left_and_right=0;//̹����ת״̬����ʱ�루right��Ϊ1��˳ʱ�루left��Ϊ-1������תΪ0

	position m_aim;//̹����׼��

	position m_lastFramePo;//��һ֡λ��
	rotation m_lastFrameRo;//��һ֡��ת

	float m_reload;//װ��ʱ��
};

/*
���ڿ���ʵ��
��¼��ɱ�������ͳ�ƶԵ����˺�
*/

#endif // !_TANK_H_
