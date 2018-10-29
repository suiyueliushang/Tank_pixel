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

	//更新相关属性
	//void update(float);

	void update(float);

	//渲染
	void render();

	//是否正在使用
	bool isEnable();

	//初始化子弹
	void shot(const int, const position&, const rotation&);

	//销毁子弹
	void unEnable();

	//击中坦克（包括伤害计算）
	bool isCollideWith(tank&);

	//击中场景
	bool isCollideWith(item&);

	//子弹属性列表
	enum properties {
		speed,
		time_to_live,
		pierce,
		damage
	};

	//获取子弹属性
	float getProperty(properties);

private:
	bool enabled;//是否正在使用

	int m_type;//类型
	position m_position;//坐标
	rotation m_rotation;//旋转
	position m_lastFram;//上一帧位置
	float m_speed;//当前速度
	float m_time_start;//发射开始时间
	float m_pierce;//当前穿透力

};


#endif // !_BULLET_H_
