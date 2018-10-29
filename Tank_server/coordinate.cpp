#include "coordinate.h"

position::position(float _x, float _y)
	:m_x(_x),m_y(_y)
{
}

float position::x()const
{
	return m_x;
}

float position::y()const
{
	return m_y;
}

float position::x(float _x)
{
	return (this->m_x = _x);

}

float position::y(float _y)
{
	return (this->m_y = _y);

}

position position::operator+(const position &b) const
{
	return position(m_x + b.m_x, m_y + b.m_y);
}

position position::operator-() const
{
	return position(-m_x,-m_y);
}

position position::operator-(const position &b) const
{
	return position(m_x - b.m_x, m_y - b.m_y);
}

position& position::operator+=( const position &chang_position)
{
	m_x += chang_position.m_x;
	m_y += chang_position.m_y;
	return *this;
}

position& position::operator-=(const position &chang_position)
{
	m_x -= chang_position.m_x;
	m_y -= chang_position.m_y;
	return *this;
}


rotation::rotation(float radian)
	:m_radian(radian)
{
	strict();
}

float rotation::r()const
{
	return m_radian;
}

float rotation::r(float radian)
{
	m_radian = radian;
	strict();
	return m_radian;
}

rotation rotation::operator+(const rotation &b)const
{
	return rotation(m_radian+b.m_radian);
}

rotation rotation::operator-() const
{
	return rotation(-m_radian);
}

rotation rotation::operator-(const rotation &b) const
{
	return rotation(m_radian - b.m_radian);
}

rotation rotation::operator+=(const rotation &chang_rotation)
{
	m_radian += chang_rotation.m_radian;
	strict();
	return *this;
}

rotation rotation::operator-=(const rotation &chang_rotation)
{
	m_radian -= chang_rotation.m_radian;
	strict();
	return *this;
}

void rotation::strict()
{
	float pi = 3.14159265359f;
	while (m_radian < 0)
		m_radian += 2 * pi;
	while (m_radian > 2 * pi)
		m_radian -= 2 * pi;
}

/*
author: rain, K024
*/
#define my_max(a,b)	   (((a) > (b)) ? (a) : (b))
#define my_min(a,b)    (((a) < (b)) ? (a) : (b))
bool cross(position p1, position p2, position q1, position q2)
{
	//预检测线段位置是否可能相交
	if (my_max(p1.x(), p2.x()) < my_min(q1.x(), q2.x()) ||
		my_max(p1.y(), p2.y()) < my_min(q1.y(), q2.y()) ||
		my_min(p1.x(), p2.x()) > my_max(q1.x(), q2.x()) ||
		my_min(p1.y(), p2.y()) > my_max(q1.y(), q2.y())
		)return false;
	//向量外积
	static auto multi = [](position a1, position a2)->float 
	{
		return a1.x()*a2.y() - a1.y()*a2.x(); 
	};
	//检测相交
	if ((multi(p1 - q1, q2 - q1)*multi(p2 - q1, q2 - q1) <= 0) && 
		(multi(q1 - p1, p2 - p1)*multi(q2 - p1, p2 - p1) <= 0))
		return true;
	return false;
};
#undef my_max
#undef my_min

