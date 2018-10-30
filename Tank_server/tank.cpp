#include "tank.h"
#include"scene.h"
#include "collision.h"
#include "render.h"
#include "timer.h"



//����̹��ͼƬ�б�
const my_render::images img_list[3][2] = {
	{my_render::tank_blue,my_render::cannon_blue},
	{my_render::tank_yellow,my_render::cannon_yellow},
	{my_render::tank_red,my_render::cannon_red}
};


tank::tank()
{
	m_status = 0;
}

tank::~tank()
{
}

/*
author: forcyan
*/
void tank::enable(
	position _position,
	rotation _rotation,
	tank_type type)
{
	m_type = type;
	m_position = _position;
	m_rotation = _rotation;
	m_status = 1; 
	m_aim = m_position + position(-500 * sin(m_rotation.r()), -500 * cos(m_rotation.r()));
	m_life = getProperty(life);
	m_reload = getProperty(load);
}

bool tank::isEnable()
{
	return m_status;
}

bool tank::isDead()
{
	return (m_status == 2 ? true : false);
}

/*
author: forcyan
*/
void tank::update(float dt)
{
	if (m_status!=1)return;
	m_lastFramePo = m_position;
	m_lastFrameRo = m_rotation;
	//��ת
	m_rotation += rotation(m_left_and_right * getProperty(rotate_speed) *dt);
	//ǰ���ƶ�
	if(m_up_and_down == 0)
	{
		//��ͣ�£����ٶ�x2
		if (m_now_speed > 0) {
			m_now_speed -= 2 * getProperty(a_speed) * dt;
			if (m_now_speed < 0)
				m_now_speed = 0;
		}

		if (m_now_speed < 0) {
			m_now_speed += 2 * getProperty(a_speed) * dt;
			if (m_now_speed > 0)
				m_now_speed = 0;
		}
	}
	else
	{
		if (m_now_speed * m_up_and_down > 0)
			//����
			m_now_speed += m_up_and_down * getProperty(a_speed) *dt;
		else
			//���٣����ٶ�x2
			m_now_speed += 2 * m_up_and_down * getProperty(a_speed) *dt;
		if (m_now_speed > getProperty(max_speed))
		{
			m_now_speed = getProperty(max_speed);
		}
		if (m_now_speed < -getProperty(max_speed))
		{
			m_now_speed = -getProperty(max_speed);
		}
	}
	m_position += position(m_now_speed * dt * -sin(m_rotation.r()), m_now_speed * dt * -cos(m_rotation.r()));

	//��ת����
	//author: K024
	float pi = 3.14159265359;
	rotation abs_rotation = atan2(m_position.x() - m_aim.x(), m_position.y() - m_aim.y());
	rotation d_rotation=m_rotation + m_cannon_rotation -abs_rotation;
	if (d_rotation.r() < pi) 
	{
		if (d_rotation.r() > getProperty(cannon_speed) * dt)
			d_rotation.r(getProperty(cannon_speed) * dt);
		m_cannon_rotation -= d_rotation;
	}
	if (d_rotation.r() > pi)
	{
		d_rotation = -d_rotation;
		if (d_rotation.r() > getProperty(cannon_speed) * dt)
			d_rotation.r(getProperty(cannon_speed) * dt);
		m_cannon_rotation += d_rotation;
	}

	m_reload -= dt;
}

void tank::update(int id, float dt, raw_input input[])
{
	if (m_status != 1)return;
	this->m_rotation += rotation(input[id].left_and_right * getProperty(rotate_speed) *dt);
	if (input[id].up_and_down == 0)
	{
		//��ͣ�£����ٶ�x2
		if (m_now_speed > 0) {
			m_now_speed -= 2 * getProperty(a_speed) * dt;
			if (m_now_speed < 0)
				m_now_speed = 0;
		}

		if (m_now_speed < 0) {
			m_now_speed += 2 * getProperty(a_speed) * dt;
			if (m_now_speed > 0)
				m_now_speed = 0;
		}
	}
	else
	{
		if (m_now_speed * input[id].up_and_down > 0)
			//����
			m_now_speed += input[id].up_and_down * getProperty(a_speed) *dt;
		else
			//���٣����ٶ�x2
			m_now_speed += 2 * input[id].up_and_down * getProperty(a_speed) *dt;
		if (m_now_speed > getProperty(max_speed))
		{
			m_now_speed = getProperty(max_speed);
		}
		if (m_now_speed < -getProperty(max_speed))
		{
			m_now_speed = -getProperty(max_speed);
		}
	}
	m_position += position(m_now_speed * dt * -sin(m_rotation.r()), m_now_speed * dt * -cos(m_rotation.r()));

	//��ת��̨
	float pi = 3.14159265359;
	rotation abs_rotation = atan2(m_position.x() - input[id].aim.x(), m_position.y() - input[id].aim.y());
	rotation d_rotation = m_rotation + m_cannon_rotation - abs_rotation;
	if (d_rotation.r() < pi)
	{
		if (d_rotation.r() > getProperty(cannon_speed) * dt)
			d_rotation.r(getProperty(cannon_speed) * dt);
		m_cannon_rotation -= d_rotation;
	}
	if (d_rotation.r() > pi)
	{
		d_rotation = -d_rotation;
		if (d_rotation.r() > getProperty(cannon_speed) * dt)
			d_rotation.r(getProperty(cannon_speed) * dt);
		m_cannon_rotation += d_rotation;
	}
	m_reload -= dt;

	
}

void tank::set_uad(int uad)
{
	m_up_and_down = uad;

}

void tank::set_lar(int lar)
{
	m_left_and_right = lar;
}

/*
author: K024
*/
void tank::render(int t)
{
	if (m_status == 0)return;
	if (t == 2) {
		//�������Ұ��û���õ�
	}
	//�ʻ��
	if (m_status == 1) {
		main_render.rend_to_scene(img_list[m_type][0], m_position, m_rotation);
		main_render.rend_to_scene(img_list[m_type][1], m_position, m_rotation + m_cannon_rotation);
		if (t == 0)main_render.rend_to_scene(my_render::aim, m_aim, rotation());
		main_render.rend_life((float)m_life / getProperty(life), t, m_position);
	}
	//������
	if (m_status == 2) {
		main_render.rend_to_scene(my_render::tank_dead, m_position, m_rotation);
		main_render.rend_to_scene(my_render::cannon_dead, m_position, m_rotation + m_cannon_rotation);
	}
}

void tank::set_aim(position aim_position)
{
	m_aim = aim_position;
}

void tank::attacked(int damage)
{
	m_life -= damage;
	if (m_life <= 0) {
		m_status = 2;

	}
}

position tank::getPosition() const
{
	return m_position;
}

rotation tank::getRotation() const
{
	return m_rotation;
}

rotation tank::getCannon() const
{
	return m_rotation+m_cannon_rotation;
}

/*
author: rain
*/
bool tank::isCollideWith(tank &b)
{
	if (m_status==0)return false;
	if (b.m_status==0)return false;
	for (int i = 0; i < 4; ++i) {
		position p1=absp(tank_collision[i],m_rotation)+m_position;
		position p2=absp(tank_collision[(i + 1 >= 4 ? 0 : i + 1)],m_rotation)+ m_position;
		main_render.rend_line(p1, p2);
		for (int j = 0; j < 4; ++j) {
			position q1 = absp(tank_collision[j], b.m_rotation)+b.m_position;
			position q2 = absp(tank_collision[(j + 1 >= 4 ? 0 : j + 1)], b.m_rotation)+b.m_position;
			main_render.rend_line(q1, q2);
			if (cross(p1, p2, q1, q2)){
				return true;
			}
		}
	}
	return false;
}

/*
author: rain
*/
bool tank::isCollideWith(item &b)
{
	if (m_status != 1)return false;
	if (!b.isEnable())return false;
	for (int i = 0; i < 4; ++i) {
		position p1 = absp(tank_collision[i], m_rotation) + m_position;
		position p2 = absp(tank_collision[(i + 1 >= 4 ? 0 : i + 1)], m_rotation) + m_position;
		main_render.rend_line(p1, p2);
		for (int j = 0; j < 7; ++j) {
			position q1 = absp(item_collisions[b.getType()][j], b.getRotation()) + b.getPosition();
			position q2 = absp(item_collisions[b.getType()][(j + 1 >= 7 ? 0 : j + 1)], b.getRotation()) + b.getPosition();
			main_render.rend_line(q1, q2);
			if (cross(p1, p2, q1, q2)) {
				return true;
			}
		}
	}
	return false;
}

/*
author: K024
*/
bool tank::shoot()
{
	if (m_status != 1)return false;
	if (m_reload > 0)return false;
	m_reload = getProperty(load);
	return true;
}

int tank::type()
{
	return m_type;
}

/*
author: K024
*/
float tank::getProperty(properties p)
{
	//����̹�������б�
	const float property_list[3][6] = {
		//  life,load,max_speed,a_speed,rotate_speed,cannon_speed,
		{	100, 1,   150,      100,    2,           2          }, //light
		{	150, 2,   120,      60,     1.3,         1.3        }, //medium
		{	200, 3,   100,      30,     1,           1          } //heavy
		
	};
	return property_list[m_type][p];
}

/*
author: K024
*/
float tank::getArmor(int i)
{
	const float armor_list[3][4] = {
		//left,buttom,right,top
		{ 8,   5,     8,    12},//light
		{ 12,  6,     12,   16},//medium
		{ 15,  12,    15,   20},//heavy
	};
	return armor_list[m_type][i];
}


/*
author: rain
*/
void tank::onCollision()
{
	m_now_speed = 0;
	m_position = m_lastFramePo;
	m_rotation = m_lastFrameRo;
}

