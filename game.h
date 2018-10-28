#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include"Server.h"

/*
game.h
游戏类

游戏入口定义
游戏场景管理
游戏主循环


*/
class game 
{
public:
	/*
	加载所有资源文件
	*/
	game();
	~game(); 

	/*
	游戏主循环
	调用对应场景的update和render
	控制场景切换
	控制帧率
	*/
	void game_cycle();

private:

	gameScene m_gameScene;
};


#endif // !_GAME_H_