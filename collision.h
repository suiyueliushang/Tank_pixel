#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "coordinate.h"

//坦克宽度的一半
const float relative_width = 15;

//坦克的碰撞模型 相对点
const position tank_collision[4] =
{ 
	position(-relative_width,-relative_width),
	position(-relative_width,relative_width),
	position(relative_width,relative_width),
	position(relative_width,-relative_width) 
};

//物件的碰撞模型 相对点
const position item_collisions[4][7] = 
{
	{//树的碰撞模型
		position(-29,-31),
		position(-29,29),
		position(-25,33),
		position(27,34),
		position(31,29),
		position(31,-30),
		position(26,-33),
	},
	{//石头的碰撞模型
		position(-11,-7),
		position(-17,-1),
		position(-17,6),
		position(-15,8),
		position(10,8),
		position(17,1),
		position(9,-9),
	},
	{//墙的碰撞模型
		position(-100,-10),
		position(-100,10),
		position(0,10),
		position(100,10),
		position(100,-10),
		position(0,-10),
		position(-50,-10),
	},
	{//边界的碰撞模型
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
计算p1相对零点逆时针旋转r弧度后的位置
*/
position absp(position p1, rotation r);

#endif // !_COLLISION_H_