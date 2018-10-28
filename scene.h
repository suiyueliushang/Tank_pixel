#ifndef _SCENE_H_
#define _SCENE_H_

#include "timer.h"
#include"input.h"
#include"bullet.h"


//ÿ�����̹������
const int max_team_tank_count = 5;

//����������
const int max_item_count = 50;

//��������ӵ�����
const int max_bullet_count = 40;



//��Ӫ��ɫ
enum team_colors {
	blue,
	red
};

class choice_single
{
public:
	choice_single();
	int choice;
	bool confirm;
	bool ready;
};

class choice_blue
{
public:
	choice_blue();
	
	bool blue_confirm[5];
	int blue_choice[5];
	bool ready;
};

class choice_red
{
public:
	choice_red();
	bool red_confirm[5];
	int red_choice[5];
	bool ready;
};

//��̬�����࣬�������ݴ���
//�����ж�̬�����ڴ棬������ຯ��static����

class _dynamicScene
{
public:
	tank tanks[2][max_team_tank_count];//����̹��
	bullet bullets[max_bullet_count];//�ӵ�
	int end;//1:����ʤ�� 0:δ��ʤ�� -1:�췽ʤ��
};



class gameScene
{
public:
	gameScene();
	~gameScene();

	void Info();

	/*
	���³�����Ϣ
	��ȡÿ֡ʱ��
	���ö�Ӧ���update
	֮������ײ�ȵ�
	*/
	void update();


	/*
	�����ײ��ִ�и��ֲ���
	������Ұ����
	*/
	void collisonhandler();

	/*
	��Ⱦ��������
	����ÿ�����render
	������Ұ����
	*/
	void render();
	
	/*
	�����Ұ������̹�˿ɼ���
	���뼺��̹����ɫ��һ���з�̹������
	*/
	void visionhandler();

private:
	bool end;

	bool sure_one;

	bool sure[10];

	bool sureAll;

	choice_blue m_choice_blue;

	choice_red m_choice_red;

	raw_input input_one;

	raw_input input[10];

	_dynamicScene dynamic_scene;

	item items[max_item_count];//�������

	team_colors team_color;//0������   1���췽
	int my_tank;//ָ��ǰ������̹��

	//�з�̹�˿ɼ��б�
	bool visible_list[max_team_tank_count];

	timer_ my_timer;

};





#endif // !_SCENE_H_