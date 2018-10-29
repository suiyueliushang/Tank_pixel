#include <graphics.h>

#include"item.h"
#include"Server.h"
#include "render.h"
#include "input.h"
#include "timer.h"
#include "scene.h"
#include "game.h"



/*
author: suiyueliushang
*/
gameScene::gameScene()
{
	

	items[0].enable(item::background, position(), rotation());
	items[1].enable(item::wall, position(-719, -757), rotation());
	items[2].enable(item::wall, position(601, -619), rotation());
	items[3].enable(item::wall, position(784, -619), rotation());
	items[4].enable(item::wall, position(-506, -384), rotation());
	items[5].enable(item::wall, position(-292, -384), rotation());
	items[6].enable(item::wall, position(-470, 69), rotation());
	items[7].enable(item::wall, position(-574, 172), rotation(1.57));
	items[8].enable(item::wall, position(-574, 368), rotation(1.57));
	items[9].enable(item::wall, position(888, 569), rotation());
	items[10].enable(item::wood, position(-4, -766), rotation());
	items[11].enable(item::wood, position(258, -371), rotation());
	items[12].enable(item::wood, position(-94, -76), rotation());
	items[13].enable(item::wood, position(610, 692), rotation());
	items[14].enable(item::wood, position(-528, 751), rotation());
	items[15].enable(item::stone, position(-326, -829), rotation());
	items[16].enable(item::stone, position(-294, -818), rotation());
	items[17].enable(item::stone, position(429, -788), rotation());
	items[18].enable(item::stone, position(-766, -487), rotation());
	items[19].enable(item::stone, position(-730, -493), rotation());
	items[20].enable(item::stone, position(33, -475), rotation());
	items[21].enable(item::stone, position(62, -455), rotation());
	items[22].enable(item::stone, position(-390, -180), rotation());
	items[23].enable(item::stone, position(793, -213), rotation());
	items[24].enable(item::stone, position(848, -182), rotation());
	items[25].enable(item::stone, position(-822, -21), rotation());
	items[26].enable(item::stone, position(862, 244), rotation());
	items[27].enable(item::stone, position(-306, 472), rotation());
	items[28].enable(item::stone, position(-727, 564), rotation());
	items[29].enable(item::stone, position(-123, 840), rotation());
	items[30].enable(item::stone, position(-37, 889), rotation());

	for (int i = 0; i < 10; i++)
		sure[i] = 0;

	sureAll = 0;
}

gameScene::~gameScene()
{
}

void gameScene::Info()
{	
	int lists[10];//lists用于存储十个客户端的连接状态
	while (1)
	{
		server.getConnections(lists);
		for (int i = 0; i < 10; i++)//循环对十个客户端分别操作
		{
			if (lists[i] != 0)//判断当前客户端状态
			{
				message_info info = server.m_recv(i);//获取当前客户端message_info
				switch ((char)(info.type))//通过当前客户端info中的type来区别信息传输
				{
				case 1://玩家进入游戏
					if (info.isNew)//当该客户端信息为新时进入
					{
						server.getContent(i, &sure_one, sizeof(sure));//获取当前客户端的“确认”信息
						sure[i] = sure_one;//将当前确认信息保存在数组中
						server.m_send(i, 1, &i, sizeof(i));//向当前客户端传递“id”值
						if (i == 9)//循环sure数组，判断十个客户端是否都进入游戏
						{
							for (int j = 0; j < 10; i++)
							{
								if (sure[i] == false)
								{
									break;
								}
								if (j == 9)
								{
									sureAll == true;
								}
							}
						}
					}
					break;
				case 3://玩家选择坦克
					if (info.isNew)
					{
						choice_single choice_one;
						server.getContent(i, &choice_one, sizeof(choice_one));//获取当前玩家选择坦克和锁定信息
						if (i < 5)//当前玩家id小于5保存在蓝色方
						{
							m_choice_blue.blue_choice[i] = choice_one.choice;
							m_choice_blue.blue_confirm[i] = choice_one.confirm;
						}
						else if (i >= 5)//当前玩家id大于5保存在红色方
						{
							m_choice_red.red_choice[i - 5] = choice_one.choice;
							m_choice_red.red_confirm[i - 5] = choice_one.confirm;
						}
						for (int j = 0; j < 5; j++)//循环用于判断十个人是否确定
						{
							if (m_choice_blue.blue_confirm[j] == false || m_choice_red.red_confirm[j] == false)
							{
								break;
							}
							if (j == 4)
							{
								m_choice_blue.ready = true;
								m_choice_red.ready = true;
							}
						}

						/*if (m_choice_blue.blue_confirm[0] == 1)
						{
							m_choice_blue.ready = true;
							m_choice_red.ready = true;
						}
					*/

						//向所有客户端发送其自己和队友的选择和锁定信息
						for (int j = 0; j < 10; j++)
						{
							if (j < 5)
							{
								server.m_send(j, 3, &m_choice_blue, sizeof(m_choice_blue));
							}
							else
							{
								server.m_send(j, 3, &m_choice_red, sizeof(m_choice_red));
							}
						}
					}
					break;
				case 4:	//玩家战斗
					static bool first = true;
					if (first)
					{
						dynamic_scene.end = 0;
						for (int i = 0; i < 5; i++)
						{
							first = false;
							dynamic_scene.tanks[blue][i].enable(position(600 + 50 * i, -900), rotation(3.14), (tank::tank_type)(m_choice_blue.blue_choice[i] > 0 ? m_choice_blue.blue_choice[i] - 1 : 1));
							dynamic_scene.tanks[red][i].enable(position(-900, 600 + 50 * i), rotation(4.71), (tank::tank_type)(m_choice_red.red_choice[i] > 0 ? m_choice_red.red_choice[i] - 1 : 1));
						}
					}
					if (info.isNew)
					{
						int blue_lives = 0;
						for (int i = 0; i < 5; i++)
						{
							if (!dynamic_scene.tanks[blue][i].isDead()) {
								blue_lives++;
							}
						}
						int red_lives = 0;
						for (int i = 0; i < 5; i++)
						{
							if (!dynamic_scene.tanks[red][i].isDead()) {
								red_lives++;
							}
						}
						if (blue_lives == 0) {
							dynamic_scene.end = -1;
						}
						else if (red_lives == 0)
						{
							dynamic_scene.end = 1;
						}

						server.m_send(i, 4, &dynamic_scene, sizeof(dynamic_scene));
						server.getContent(i, &input_one, sizeof(input_one));//接收当前客户端的input信息
						input[i] = input_one;//将当前input信息存储在input数组中
						//if (i == 9)//通过input数组对当前信息进行update和collisionhandler
						//{
						this->update();
						this->collisonhandler();
						//for (int j = 0; j < 10; j++)//update和collisionhandler之后向十个客户端发送dynamic_sence
						//{
						//	server.m_send(j, 4, &dynamic_scene, sizeof(dynamic_scene));
						//}
					}
					break;
				}
			}
		}
		delay_fps(60);
	}
}

/*
author: forcyan
*/
void gameScene::update()
{
	float dt = my_timer.stop();
	if (dt < 1e-11)
		dt = 0.016;
	my_timer.start();

	//	//处理控件输入消息
	//	static raw_input r_input;
	//	r_input.get_raw();
	//	leftbar.check(r_input, &dt);
	//	rightbar.check(r_input, &dt);
	//	topbar.check(r_input, &dt);
	//	buttombar.check(r_input, &dt);
	for (int i = 0; i < 10; i++)
	{
		int color = i / 5;
		int team_id = i % 5;
		auto&r_input = input[i];
		if (!map.check(r_input, nullptr))
			//没有左键点击小地图
			//作为坦克点击输入
			if (tank_input.check(r_input, &dynamic_scene.tanks[color][team_id])) {
				//遍历子弹池发射子弹
				for (auto &i : dynamic_scene.bullets) {
					if (!i.isEnable()) {
						i.shot(dynamic_scene.tanks[color][team_id].type(),
							dynamic_scene.tanks[color][team_id].getPosition(),
							dynamic_scene.tanks[color][team_id].getCannon());
						break;
					}
				}
			}
	}
	//
	//
		/*
		场景更新
		*/
	int count = 0;

	for (auto& each : dynamic_scene.tanks[blue])
	{
		each.update(dt);
	}
	for (auto& each : dynamic_scene.tanks[red])
	{
		each.update(dt);
	}

	count = 0;

	for (auto& each : dynamic_scene.bullets)
	{
		each.update(dt);
	}

}

/*
author: rain
*/
void gameScene::collisonhandler()
{
	//检测blue team内碰撞
	for (int i = 0; i < max_team_tank_count; ++i)
	{
		//减少次数
		for (int j = i + 1; j < max_team_tank_count; ++j)
		{
			if (dynamic_scene.tanks[blue][i].isCollideWith(dynamic_scene.tanks[blue][j]))
			{
				dynamic_scene.tanks[blue][i].onCollision();
				dynamic_scene.tanks[blue][j].onCollision();
			}
		}
		//检测场景碰撞
		for (auto &j : items) {
			if (dynamic_scene.tanks[blue][i].isCollideWith(j))
				dynamic_scene.tanks[blue][i].onCollision();
		}
	}
	//检测red team内碰撞
	for (int i = 0; i < max_team_tank_count; ++i)
	{
		//减少次数
		for (int j = i + 1; j < max_team_tank_count; ++j)
		{
			if (dynamic_scene.tanks[red][i].isCollideWith(dynamic_scene.tanks[red][j])) 
			{
				dynamic_scene.tanks[red][i].onCollision();
				dynamic_scene.tanks[red][j].onCollision();
			}
		}
		//检测场景碰撞
		for (auto &j : items) {
			if (dynamic_scene.tanks[red][i].isCollideWith(j))
				dynamic_scene.tanks[red][i].onCollision();
		}
	}
	//检测两队坦克之间
	for (int i = 0; i < max_team_tank_count; ++i) {
		for (int j = 0; j < max_team_tank_count; ++j) {
			if (dynamic_scene.tanks[blue][i].isCollideWith(dynamic_scene.tanks[red][j])) {
				dynamic_scene.tanks[blue][i].onCollision();
				dynamic_scene.tanks[red][j].onCollision();
			}
		}
	}
	//检测子弹碰撞
	for (int i = 0; i < max_bullet_count; ++i)
	{
		for (int k = 0; k < 2; ++k)
		{
			for (int j = 0; j < max_team_tank_count; ++j)
			{
				dynamic_scene.bullets[i].isCollideWith(dynamic_scene.tanks[k][j]);
			}
		}
		for (auto &j : items) {
			dynamic_scene.bullets[i].isCollideWith(j);
		}
	}
}

/*
author: forcyan
*/
void gameScene::render()
{		
	/*
	场景渲染
	*/
	//渲染物件
	for (auto& each : items) {
		each.render();
	}
	//渲染blue team坦克
	for (int i=0;i<max_team_tank_count;i++)
	{
		auto& each = dynamic_scene.tanks[blue][i];
		if (&each == &dynamic_scene.tanks[team_color][my_tank])
			each.render(0);//自己
		else if (team_color == blue)
			each.render(1);//队友
		else if (visible_list[i]) 
			each.render(2);//对手
	}
	//渲染red team坦克
	for (int i = 0; i < max_team_tank_count; i++)
	{
		auto& each = dynamic_scene.tanks[red][i];
		if (&each == &dynamic_scene.tanks[team_color][my_tank])
			each.render(0);//自己
		else if (team_color == red)
			each.render(1);//队友
		else if (visible_list[i])
			each.render(2);//对手
	}
	//渲染子弹
	for (auto& each : dynamic_scene.bullets)
	{
		each.render();
	}
	//渲染小地图
	main_render.rend_map(4, position());
	for (int i = 0; i < max_team_tank_count; i++)
	{
		auto& each = dynamic_scene.tanks[blue][i];
		if (!each.isEnable())continue;
		if (each.isDead())
			main_render.rend_map(3, each.getPosition());
		else if (&each == &dynamic_scene.tanks[team_color][my_tank])
			main_render.rend_map(0, each.getPosition());
		else if(team_color==blue)
			main_render.rend_map(1, each.getPosition());
		else if (visible_list[i])
			main_render.rend_map(2, each.getPosition());
	}
	for (int i = 0; i < max_team_tank_count; i++)
	{
		auto& each = dynamic_scene.tanks[red][i];
		if (!each.isEnable())continue;
		if (each.isDead())
			main_render.rend_map(3, each.getPosition());
		else if (&each == &dynamic_scene.tanks[team_color][my_tank])
			main_render.rend_map(0, each.getPosition());
		else if (team_color == red)
			main_render.rend_map(1, each.getPosition());
		else if (visible_list[i])
			main_render.rend_map(2, each.getPosition());
	}
	
}

/*
author: suiyueliushang
*/
void gameScene::visionhandler()
{
	//遍历敌方坦克
	for (int i = 0; i < max_team_tank_count; i++) {
		auto&t = dynamic_scene.tanks[1 - team_color][i];
		visible_list[i] = false;
		if (!t.isEnable())continue;
		//遍历己方坦克
		for (auto&each : dynamic_scene.tanks[team_color]) 
		{
			if (!each.isEnable())continue;
			if (each.isDead())continue;
			bool isSeen = true;
			//遍历物件检测遮挡
			for (auto&i : items) {
				//有一个物件遮挡则相互不可见
				if (i.isCrossed(t.getPosition(), each.getPosition())) {
					isSeen = false;
					break;
				}
			}
			//有己方坦克能看到则渲染
			if (isSeen) {
				visible_list[i] = true;
				break;
			}
		}
	}

}

//menuScene::menuScene()
//{
//	
//}
//
//menuScene::~menuScene()
//{
//
//}

choice_single::choice_single()
{
	confirm = 0;
	choice = 0;
	ready = 0;
}

choice_blue::choice_blue()
{
	for (int i = 0; i < 5; i++)
	{
		blue_choice[i] = 0;
		blue_confirm[i] = 0;
	}
	ready = 0;
}

choice_red::choice_red()
{
	for (int i = 0; i < 5; i++)
	{
		red_choice[i] = 0;
		red_confirm[i] = 0;
	}
	ready = 0;
}
