#include "game.h"
#define SHOW_CONSOLE
#include <graphics.h>
#include "render.h"
//#include <iostream>

game::game()
{
	initgraph(1080, 720);
	main_render.init();
}

game::~game()
{
}



void game::game_cycle()
{
	message_info m_info;
	if (m_menuScene.is_start())
			client.m_send(1, &m_menuScene.m_start , 1);
		m_info = client.m_recv();
		if (1==m_info.type&&true== m_info.isNew)
			client.getContent(&m_menuScene.id, 4);//ªÒ»°id∫≈
	{
		cleardevice();
		m_menuScene.render(0);
		m_menuScene.render(2);
	}
	m_menuScene.wait(); 
	m_menuScene.render(3);
	while (1)
	{
		m_menuScene.getChoice();
		client.m_send(3, &myChoice, 8);
		m_info = client.m_recv();
		if (true == m_info.isNew && 3 == m_info.type)
			client.getContent(&f_ch, sizeof(friend_choice));
		m_menuScene.render(4);
		if (1 == f_ch.is_playing)
			break;
	}

	while(1)
	{
		if (!retVal)
		{
			m_gameScene.update();
			m_gameScene.collisonhandler();
		}
		raw_input m_input;
		m_input.get_raw();
		client.m_send(4, &m_input, sizeof(m_input));
		m_info = client.m_recv();
		if (1 == m_info.isNew && 4 == m_info.type)
		{
			client.getContent(&m_gameScene.dynamic_scene, sizeof(m_gameScene.dynamic_scene));
		}
		if (0 != m_gameScene.dynamic_scene.end)
			break;
		m_gameScene.visionhandler();
		cleardevice();
		m_gameScene.render();
		delay_fps(120);
	}
	if (-1 == m_gameScene.dynamic_scene.end)
		main_render.rend_to_scene(my_render::defeat,position(540,360),0);
	else
		if(1== m_gameScene.dynamic_scene.end)
			main_render.rend_to_scene(my_render::victory, position(540, 360), 0);
	getch();
}