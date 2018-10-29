#include "timer.h"
#define SHOW_CONSOLE
#include <graphics.h>
#include "scene.h"
#include "render.h"
#include "input.h"
#include"game.h"
const my_render::images img = my_render::start;

/*
author: suiyueliushang
*/
gameScene::gameScene()
{
	dynamic_scene.tanks[blue][0].enable(position(), rotation(), tank::light);
	dynamic_scene.tanks[blue][1].enable(position(0, -100), rotation(), tank::medium);
	dynamic_scene.tanks[red][0].enable(position(100, 0), rotation(1), tank::heavy);
	dynamic_scene.tanks[red][1].enable(position(100, 100), rotation(), tank::heavy);
	my_tank = 0;
	team_color = blue;

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
}


gameScene::~gameScene()
{
}
//
//bool gameScene::recvInfo(Client &c)
//{
//
//	bool m = c.receive(dynamic_scene);
//
//	return(m);
//}

/*
author: forcyan
*/
void gameScene::update()
{
	float dt = my_timer.stop();
	if (dt < 1e-11)
		dt = 0.016;
	my_timer.start();

	//����ؼ�������Ϣ
	static raw_input r_input;
	r_input.get_raw();
	leftbar.check(r_input, &dt);
	rightbar.check(r_input, &dt);
	topbar.check(r_input, &dt);
	buttombar.check(r_input, &dt);
	if (!map.check(r_input, nullptr));
		//û��������С��ͼ
		//��Ϊ̹�˵������
		//if (tank_input.check(r_input, &dynamic_scene.tanks[team_color][my_tank])) {
		//	//�����ӵ��ط����ӵ�
		//	for (auto &i : dynamic_scene.bullets) {
		//		if (!i.isEnable()) {
		//			i.shot(dynamic_scene.tanks[team_color][my_tank].type(),
		//				dynamic_scene.tanks[team_color][my_tank].getPosition(),
		//				dynamic_scene.tanks[team_color][my_tank].getCannon());
		//			break;
		//		}
		//	}
		//}


	/*
	��������
	*/
	for (auto& each : dynamic_scene.tanks[blue])
	{
		each.update(dt);
	}
	for (auto& each : dynamic_scene.tanks[red])
	{
		each.update(dt);
	}

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
	//���blue team����ײ
	for (int i = 0; i < max_team_tank_count; ++i)
	{
		//���ٴ���
		for (int j = i + 1; j < max_team_tank_count; ++j)
		{
			if (dynamic_scene.tanks[blue][i].isCollideWith(dynamic_scene.tanks[blue][j]))
			{
				dynamic_scene.tanks[blue][i].onCollision();
				dynamic_scene.tanks[blue][j].onCollision();
			}
		}
		//��ⳡ����ײ
		for (auto &j : items) {
			if (dynamic_scene.tanks[blue][i].isCollideWith(j))
				dynamic_scene.tanks[blue][i].onCollision();
		}
	}
	//���red team����ײ
	for (int i = 0; i < max_team_tank_count; ++i)
	{
		//���ٴ���
		for (int j = i + 1; j < max_team_tank_count; ++j)
		{
			if (dynamic_scene.tanks[red][i].isCollideWith(dynamic_scene.tanks[red][j])) 
			{
				dynamic_scene.tanks[red][i].onCollision();
				dynamic_scene.tanks[red][j].onCollision();
			}
		}
		//��ⳡ����ײ
		for (auto &j : items) {
			if (dynamic_scene.tanks[red][i].isCollideWith(j))
				dynamic_scene.tanks[red][i].onCollision();
		}
	}
	//�������̹��֮��
	for (int i = 0; i < max_team_tank_count; ++i) {
		for (int j = 0; j < max_team_tank_count; ++j) {
			if (dynamic_scene.tanks[blue][i].isCollideWith(dynamic_scene.tanks[red][j])) {
				dynamic_scene.tanks[blue][i].onCollision();
				dynamic_scene.tanks[red][j].onCollision();
			}
		}
	}
	//����ӵ���ײ
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
	������Ⱦ
	*/
	//��Ⱦ���
	for (auto& each : items) {
		each.render();
	}
	//��Ⱦblue team̹��
	for (int i=0;i<max_team_tank_count;i++)
	{
		auto& each = dynamic_scene.tanks[blue][i];
		if (&each == &dynamic_scene.tanks[team_color][my_tank])
			each.render(0);//�Լ�
		else if (team_color == blue)
			each.render(1);//����
		else if (visible_list[i]) 
			each.render(2);//����
	}
	//��Ⱦred team̹��
	for (int i = 0; i < max_team_tank_count; i++)
	{
		auto& each = dynamic_scene.tanks[red][i];
		if (&each == &dynamic_scene.tanks[team_color][my_tank])
			each.render(0);//�Լ�
		else if (team_color == red)
			each.render(1);//����
		else if (visible_list[i])
			each.render(2);//����
	}
	//��Ⱦ�ӵ�
	for (auto& each : dynamic_scene.bullets)
	{
		each.render();
	}
	//��ȾС��ͼ
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
	//�����з�̹��
	for (int i = 0; i < max_team_tank_count; i++) {
		auto&t = dynamic_scene.tanks[1 - team_color][i];
		visible_list[i] = false;
		if (!t.isEnable())continue;
		//��������̹��
		for (auto&each : dynamic_scene.tanks[team_color]) 
		{
			if (!each.isEnable())continue;
			if (each.isDead())continue;
			bool isSeen = true;
			//�����������ڵ�
			for (auto&i : items) {
				//��һ������ڵ����໥���ɼ�
				if (i.isCrossed(t.getPosition(), each.getPosition())) {
					isSeen = false;
					break;
				}
			}
			//�м���̹���ܿ�������Ⱦ
			if (isSeen) {
				visible_list[i] = true;
				break;
			}
		}
	}

}



menuScene::menuScene()
{
}

menuScene::~menuScene()
{

}

bool menuScene::is_start()
{
	while (1)
	{
		render(0);
		render(1);
		raw_input m_raw_input;
		m_raw_input.get_raw();
		if (start.check(m_raw_input, NULL))
		{
			m_start = 1;
			return true;
			delay_fps(20);
		}
	}
}

void menuScene::render(int m_i)
{
	switch (m_i)
	{
	case 0:
		main_render.rend_to_scene(my_render::main_game, 0, 0);
		break;
	case 1:
		main_render.rend_to_scene(my_render::start, 0, 0);
		break;
	case 2:
		main_render.rend_to_scene(my_render::wait, 0, 0);
		break;
	case 3:
		main_render.rend_to_scene(my_render::choice, 0, 0);
		break;
	case 4:
		/*raw_input input;
		main_render.rend_to_scene(my_render::cover, 868, 97 + (id - 1) * 144);
		if (choose1.check(input, NULL))
			main_render.rend_to_scene(my_render::tank_1, 988, 97 + (id - 1) * 144);
		else
			if (choose2.check(input, NULL))
				main_render.rend_to_scene(my_render::tank_2, 988, 97 + (id - 1) * 144);
			else
				if(choose3.check(input, NULL))
					main_render.rend_to_scene(my_render::tank_3, 988, 97 + (id - 1) * 144);

		if(confirm.check(input, NULL))
			main_render.rend_to_scene(my_render::sure, 1019, 137 + (id - 1) * 144);*/
	{
		for (int i = 1; i <= 5; i++)
		{

			switch (f_ch.f_choice[i])
			{
			case 1:
				main_render.rend_to_scene(my_render::tank_1, position(448, -236 + (i - 1) * 144),rotation());
				break;
			case 2:
				main_render.rend_to_scene(my_render::tank_2, position(448, -236 + (i - 1) * 144), rotation());
				break;
			case 3:
				main_render.rend_to_scene(my_render::tank_3, position(448, -236 + (i - 1) * 144), rotation());
				break;
			default:
				break;
			}

			if (f_ch.f_is_sure[i])
			{
				main_render.rend_to_scene(my_render::sure, 479, -223 + (i - 1) * 144);
			}
		}

	}
	default:
		break;
	}
	
}


void menuScene::wait()
{
	message_info m_info;
	bool is_return = 0;//�Ǹ�����Ƿ񶼽���ȷ��
	while (1)
	{
		m_info = client.m_recv();
		if (1 == m_info.isNew && 2 == m_info.type)
		{
			client.getContent(&is_return, 1);
			if (1 == is_return)
				return;
		}
	}
}

void menuScene::getChoice()
{
	raw_input m_input;
	m_input.get_raw();
	if (choose1.check(m_input, NULL))
	      myChoice.m_choice = 1;
	else
		if (choose2.check(m_input, NULL))
			myChoice.m_choice = 2;
		else
			if (choose3.check(m_input, NULL))
				myChoice.m_choice = 2;
	if (confirm.check(m_input, NULL))
	{
		myChoice.is_sure = 1;
	}
}

//void menuScene::choose(Client &c)
//{
//	raw_input input;
//	while (1)
//	{
//		input.get_raw();
//		if (choose1.check(input, NULL))
//		{
//			c.Send(1);
//			c.receive();
//			break;
//		}
//		else if (choose2.check(input, NULL))
//		{
//			c.Send(2);
//			c.receive();
//			break;
//		}
//		else if (choose3.check(input, NULL))
//		{
//			c.Send(3);
//			c.receive();
//			break;
//		}
//		else if (confirm.check(input, NULL))
//		{
//			c.Send(4);
//			c.receive();
//			break;
//		}
//	}
//    
//}
//
//bool menuScene::fight()
//{
//	return isFight;
//}

friend_choice f_ch;//������Ϣ
choice myChoice;//ѡ���̹�ˣ��Լ��Ƿ�ȷ�ϣ�
m_client client;//�ͻ���