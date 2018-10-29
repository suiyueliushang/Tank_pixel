#ifndef _ITEM_H_
#define _ITEM_H_

#include "coordinate.h"


class item
{
public:
	item();
	~item();

	//物件类型枚举类
	enum types {
		wood,
		stone,
		wall,
		background
	};

	position getPosition()const;
	rotation getRotation()const;

	//启用物件
	void enable(types, position, rotation);

	int getType();
	bool isEnable();
	void render();

	//判断线段是否穿过物件
	bool isCrossed(position,position);

private:

	bool m_enabled;
	types m_type;
	position m_position;
	rotation m_rotation;

};




#endif // !_ITEM_H_
