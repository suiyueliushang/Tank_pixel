#include<cmath>
#include "bullet.h"
#include "collision.h"
#include "render.h"
#include "timer.h"
#include"scene.h"

bullet::bullet()
{
	enabled = false;
}

bullet::~bullet()
{

}

/*
author: forcyan
*/
void bullet::update(float dt)
{
	if (!enabled)return;
	m_lastFram = m_position;
	//�ӵ����У�λ�øı�
	m_position += position(m_speed *dt * -sin(m_rotation.r()), m_speed*dt*-cos(m_rotation.r()));
	m_speed -= dt * 30;
	m_pierce -= dt * 5;
	//�ж�������
	if ((my_clock() - m_time_start) > getProperty(time_to_live))
		enabled = false;
}

/*
author: forcyan
*/
void bullet::render()
{
	if (!enabled)return;
	main_render.rend_to_scene(my_render::bullet, m_position, m_rotation);
}

bool bullet::isEnable()
{
	return enabled;
}

/*
author: forcyan
*/
void bullet::shot(const int type, const position &p, const rotation &r)
{
	this->m_type = type;
	m_speed = getProperty(speed);
	m_pierce = getProperty(pierce);
	m_time_start = my_clock();
	m_position = p + position(23 * -sin(r.r()), 23 * -cos(r.r()));
	m_rotation = r;
	enabled = true;
}

void bullet::unEnable()
{
	enabled = false;
}

/*
author: rain
*/
bool bullet::isCollideWith(tank &c)
{
	if (!enabled)return false;
	if (!c.isEnable())return false;
	main_render.rend_line(m_lastFram, m_position);
	//����̹��ÿ����
	for (int i = 0; i < 4; ++i)
	{
		//������Ե�
		position p1 = absp(tank_collision[i], c.getRotation()) + c.getPosition();
		position p2 = absp(tank_collision[(i + 1 >= 4 ? 0 : i + 1)], c.getRotation()) + c.getPosition();
		//�ж��ཻ
		if (cross(p1, p2, m_lastFram, m_position))
		{
			//�����Чװ��
			rotation armor = c.getRotation() + (3.14159265359f / 2 * (i - 1));
			rotation angle_of_rotation;
			if (armor.r() >= m_rotation.r())
			{
				angle_of_rotation = armor - m_rotation;
			}
			else
			{
				angle_of_rotation = m_rotation - armor;
			}
			float real_pierce = m_pierce * cos(angle_of_rotation.r());
			//�ܹ�����
			if (real_pierce > c.getArmor(i))
			{
				c.attacked(getProperty(damage));
			}
			//�����ӵ�
			enabled = false;
			return true;
		}
	}
	return false;
}

/*
author: rain
*/
bool bullet::isCollideWith(item &c)
{
	if (!enabled)return false;
	if (!c.isEnable())return false;
	//��������ÿ����
	for (int i = 0; i < 7; ++i)
	{
		//�����������
		position p1 = absp(item_collisions[c.getType()][i], c.getRotation()) + c.getPosition();
		position p2 = absp(item_collisions[c.getType()][(i + 1 >= 7 ? 0 : i + 1)], c.getRotation()) + c.getPosition();
		//����ཻ
		if (cross(p1, p2, m_lastFram, m_position))
		{
			//�����ӵ�
			enabled = false;
			return true;
		}
	}
	return false;
}

/*
author: K024
*/
float bullet::getProperty(properties p)
{
	const float property_list[3][4] = {
		//�����б�
		//speed,time_to_live,pierce,damage
		{ 400,  4,           30,    50}, //light tank
		{ 450,  4,           40,    70}, //mediun tank
		{ 500,  4,           50,    100}, //heavy tank
	};
	return property_list[m_type][p];
}
