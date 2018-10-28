#include "item.h"
#include "collision.h"
#include "render.h"

/*
author: suiyueliushang
*/
const my_render::images imglist[]{
    my_render::wood,
	my_render::stone,
	my_render::wall,
	my_render::background
};


item::item()
{
	m_enabled = false;
}

item::~item()
{
}

position item::getPosition() const
{
	return m_position;
}

rotation item::getRotation() const
{
	return m_rotation;
}

/*
author: suiyueliushang
*/
void item::enable(types en_item_type, position en_position, rotation en_rotation)
{
	m_enabled = true;
	m_position = en_position;
	m_rotation = en_rotation;
	m_type = en_item_type;
}

int item::getType()
{
	return m_type;
}

bool item::isEnable()
{
	return m_enabled;
}

/*
author: suiyueliushang
*/
void item::render()
{
	if (!m_enabled)return;
	main_render.rend_to_scene(imglist[m_type], m_position, m_rotation);
}

/*
author: suiyueliushang
*/
bool item::isCrossed(position p1, position p2)
{
	if (!m_enabled)
		return false;
	//遍历自身边框
	for (int i = 0; i < 7; ++i)
	{
		position q1 = absp(item_collisions[m_type][i], m_rotation) + m_position;
		position q2 = absp(item_collisions[m_type][(i + 1 >= 7 ? 0 : i + 1)], m_rotation) + m_position;
		//检测相交
		if (cross(p1, p2, q1,q2))
		{
			return true;
		}
	}
	return false;
}
