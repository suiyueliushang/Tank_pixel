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
		light,//轻型坦克
		medium,//中型坦克
		heavy//重型坦克
	};

	void enable(position, rotation, tank_type);
	bool isEnable();

	bool isDead();

	/*
	更新函数
	每一帧调用
	更新坦克各种状态
	*/
	//void update(float);

	void update(int, float, raw_input[]);
	void update(float);

	/*
	设置坦克移动状态
	*/
	void set_uad(int);

	/*
	设置坦克旋转状态
	*/
	void set_lar(int);

	position getPosition()const;
	rotation getRotation()const;
	rotation getCannon()const;

	/*
	渲染
	每帧调用
	按照当前位置和旋转角将坦克渲染到屏幕上
	int 0:自己
	    1:队友
	    2:敌方
	*/
	void render(int);

	/*
	坦克发生碰撞，回到上一帧位置且速度归零
	*/
	void onCollision();

	/*
	设置瞄准点
	*/
	void set_aim(position);

	//减少生命值
	void attacked(int);

	bool isCollideWith(tank&);

	bool isCollideWith(item&);

	//开炮（到达装填时间返回true，不负责子弹的发射）
	bool shoot();

	int type();

	//属性枚举类
	enum properties {
		life,
		load,
		max_speed,
		a_speed,
		rotate_speed,
		cannon_speed,
	};

	//获取属性
	float getProperty(properties);

	//获取第N条边的装甲厚度
	//0为左，逆时针
	float getArmor(int);

private:

	int m_status;
	tank_type m_type;

	float m_life;

	position m_position;//坦克自身位置
	rotation m_rotation;//坦克自身旋转角
	rotation m_cannon_rotation=0;//炮台相对旋转角

	float m_now_speed=0;//坦克现在速度

	int m_up_and_down=0;//坦克移动状态，向前加速为1,向后加速为-1,无动力为0
	int m_left_and_right=0;//坦克旋转状态，逆时针（right）为1，顺时针（left）为-1，无旋转为0

	position m_aim;//坦克瞄准点

	position m_lastFramePo;//上一帧位置
	rotation m_lastFrameRo;//上一帧旋转

	float m_reload;//装填时间
};

/*
后期考虑实现
记录击杀数，最后统计对敌人伤害
*/

#endif // !_TANK_H_
