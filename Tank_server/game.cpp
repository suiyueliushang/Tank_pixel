#include <graphics.h>
#include "game.h"
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
	m_gameScene.Info();
}