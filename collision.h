#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "coordinate.h"

//̹�˿�ȵ�һ��
const float relative_width = 15;

//̹�˵���ײģ�� ��Ե�
const position tank_collision[4] =
{ 
	position(-relative_width,-relative_width),
	position(-relative_width,relative_width),
	position(relative_width,relative_width),
	position(relative_width,-relative_width) 
};

//�������ײģ�� ��Ե�
const position item_collisions[4][7] = 
{
	{//������ײģ��
		position(-29,-31),
		position(-29,29),
		position(-25,33),
		position(27,34),
		position(31,29),
		position(31,-30),
		position(26,-33),
	},
	{//ʯͷ����ײģ��
		position(-11,-7),
		position(-17,-1),
		position(-17,6),
		position(-15,8),
		position(10,8),
		position(17,1),
		position(9,-9),
	},
	{//ǽ����ײģ��
		position(-100,-10),
		position(-100,10),
		position(0,10),
		position(100,10),
		position(100,-10),
		position(0,-10),
		position(-50,-10),
	},
	{//�߽����ײģ��
		position(-1000,-1000),
		position(-1000,0),
		position(-1000,1000),
		position(0,1000),
		position(1000,1000),
		position(1000,-1000),
		position(0,-1000),
	}

};

/*
����p1��������ʱ����תr���Ⱥ��λ��
*/
position absp(position p1, rotation r);

#endif // !_COLLISION_H_