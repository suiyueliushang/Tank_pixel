#ifndef _SCENE_H_
#define _SCENE_H_

#include "bullet.h"
#include "tank.h"
#include "timer.h"
#include"my_socket.h"
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

//动态场景类，用于数据传输
//不能有动态分配内存，或各种类函数static变量
class _dynamicScene {
public:

	tank tanks[2][max_team_tank_count];//两队坦克
	bullet bullets[max_bullet_count];//子弹
	int end;//是否结束游戏,-1代表输，1代表赢；
};

class gameScene
{
public:
	gameScene();
	~gameScene();

	//void sendInfo(Client&);
	//bool recvInfo(Client&);

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

	_dynamicScene dynamic_scene;
private:
	item items[max_item_count];//场景物件

	team_colors team_color;//0：蓝方   1：红方
	int my_tank;//指向当前操作的坦克

	//敌方坦克可见列表
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
	bool m_start=0;//是否点击开始游戏按钮
	int id;//玩家游戏编号

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
	int f_choice[5];//队友选择
	bool f_is_sure[5];//队友是否确认选择
	bool is_playing;//是否进入游戏
};
extern friend_choice f_ch;//队友信息
extern choice myChoice;//选择的坦克，以及是否确认；
extern m_client client;//客户端
#endif // !_SCENE_H_