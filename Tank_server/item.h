#ifndef _ITEM_H_
#define _ITEM_H_

#include "coordinate.h"


class item
{
public:
	item();
	~item();

	//�������ö����
	enum types {
		wood,
		stone,
		wall,
		background
	};

	position getPosition()const;
	rotation getRotation()const;

	//�������
	void enable(types, position, rotation);

	int getType();
	bool isEnable();
	void render();

	//�ж��߶��Ƿ񴩹����
	bool isCrossed(position,position);

private:

	bool m_enabled;
	types m_type;
	position m_position;
	rotation m_rotation;

};




#endif // !_ITEM_H_
