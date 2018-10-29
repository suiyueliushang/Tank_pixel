#ifndef _SCENE_H_
#define _SCENE_H_

#include "bullet.h"
#include "tank.h"
#include "timer.h"
#include"my_socket.h"
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

//��̬�����࣬�������ݴ���
//�����ж�̬�����ڴ棬������ຯ��static����
class _dynamicScene {
public:

	tank tanks[2][max_team_tank_count];//����̹��
	bullet bullets[max_bullet_count];//�ӵ�
	int end;//�Ƿ������Ϸ,-1�����䣬1����Ӯ��
};

class gameScene
{
public:
	gameScene();
	~gameScene();

	//void sendInfo(Client&);
	//bool recvInfo(Client&);

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

	_dynamicScene dynamic_scene;
private:
	item items[max_item_count];//�������

	team_colors team_color;//0������   1���췽
	int my_tank;//ָ��ǰ������̹��

	//�з�̹�˿ɼ��б�
	bool visible_list[max_team_tank_count];

	timer_ my_timer;

	/*menu_control m_control;*/
};

class menuScene
{
public:
	menuScene();
	~menuScene();
	bool is_start();
    
	void render(int);

	void wait();
	//void choose(Client&);
	bool m_start=0;//�Ƿ�����ʼ��Ϸ��ť
	int id;//�����Ϸ���

	void getChoice();
	

	

	
private:

};

class choice
{
public:
	int m_choice;
	bool is_sure=0;
};

class friend_choice 
{
public:
	int f_choice[5];//����ѡ��
	bool f_is_sure[5];//�����Ƿ�ȷ��ѡ��
	bool is_playing;//�Ƿ������Ϸ
};
extern friend_choice f_ch;//������Ϣ
extern choice myChoice;//ѡ���̹�ˣ��Լ��Ƿ�ȷ�ϣ�
extern m_client client;//�ͻ���
#endif // !_SCENE_H_