#ifndef _SCENE_H_
#define _SCENE_H_

#include "timer.h"
#include"input.h"
#include"bullet.h"


//每队最大坦克数量
const int max_team_tank_count = 5;

//最大物件数量
const int max_item_count = 50;

//场景最大子弹数量
const int max_bullet_count = 40;



//阵营颜色
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

//动态场景类，用于数据传输
//不能有动态分配内存，或各种类函数static变量

class _dynamicScene
{
public:
	tank tanks[2][max_team_tank_count];//两队坦克
	bullet bullets[max_bullet_count];//子弹
	int end;//1:蓝方胜利 0:未分胜负 -1:红方胜利
};



class gameScene
{
public:
	gameScene();
	~gameScene();

	void Info();

	/*
	更新场景信息
	获取每帧时间
	调用对应物件update
	之后检测碰撞等等
	*/
	void update();


	/*
	检测碰撞，执行各种操作
	包含视野控制
	*/
	void collisonhandler();

	/*
	渲染整个场景
	调用每个物件render
	包含视野控制
	*/
	void render();
	
	/*
	检测视野，控制坦克可见性
	传入己方坦克颜色和一辆敌方坦克引用
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

	item items[max_item_count];//场景物件

	team_colors team_color;//0：蓝方   1：红方
	int my_tank;//指向当前操作的坦克

	//敌方坦克可见列表
	bool visible_list[max_team_tank_count];

	timer_ my_timer;

};





#endif // !_SCENE_H_