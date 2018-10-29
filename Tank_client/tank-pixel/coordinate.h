#ifndef _COORDINATE_H_
#define _COORDINATE_H_

/*
坐标

x向右为正
y向下为正
*/
class position
{
public:
	position(float x = 0, float y = 0);

	float x()const;
	float y()const;
	float x(float);
	float y(float);

	position operator+(const position&)const;
	position operator-()const;
	position operator-(const position&)const;
	position& operator+=(const position&);
	position& operator-=(const position&);


private:
	float m_x;
	float m_y;
};


/*
旋转

弧度制
逆时针为正
向上为0
*/
class rotation
{
public:

	rotation(float radian=0);

	float r()const;

	float r(float radian);

	rotation operator+(const rotation&)const;
	rotation operator-()const;
	rotation operator-(const rotation&)const;
	rotation operator+=(const rotation&);
	rotation operator-=(const rotation&);
	
	

private:

	float m_radian;
	void strict();
};

/*
检测线段p1->p2和q1->q2是否相交
*/
bool cross(position p1, position p2, position q1, position q2);


#endif // !_COORDINATE_H_

