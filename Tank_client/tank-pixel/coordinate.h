#ifndef _COORDINATE_H_
#define _COORDINATE_H_

/*
����

x����Ϊ��
y����Ϊ��
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
��ת

������
��ʱ��Ϊ��
����Ϊ0
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
����߶�p1->p2��q1->q2�Ƿ��ཻ
*/
bool cross(position p1, position p2, position q1, position q2);


#endif // !_COORDINATE_H_

