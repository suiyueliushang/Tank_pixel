#ifndef _BULLET_H_
#define _BULLET_H_

#include "coordinate.h"
#include "tank.h"
#include "item.h"


class bullet
{
public:
	bullet();
	~bullet();

	//�����������
	//void update(float);

	void update(float);

	//��Ⱦ
	void render();

	//�Ƿ�����ʹ��
	bool isEnable();

	//��ʼ���ӵ�
	void shot(const int, const position&, const rotation&);

	//�����ӵ�
	void unEnable();

	//����̹�ˣ������˺����㣩
	bool isCollideWith(tank&);

	//���г���
	bool isCollideWith(item&);

	//�ӵ������б�
	enum properties {
		speed,
		time_to_live,
		pierce,
		damage
	};

	//��ȡ�ӵ�����
	float getProperty(properties);

private:
	bool enabled;//�Ƿ�����ʹ��

	int m_type;//����
	position m_position;//����
	rotation m_rotation;//��ת
	position m_lastFram;//��һ֡λ��
	float m_speed;//��ǰ�ٶ�
	float m_time_start;//���俪ʼʱ��
	float m_pierce;//��ǰ��͸��

};


#endif // !_BULLET_H_
