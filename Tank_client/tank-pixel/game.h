#ifndef _GAME_H_
#define _GAME_H_

#include"scene.h"
#include"input.h"
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
	menuScene m_menuScene;
	gameScene m_gameScene;
private:
	friend_choice f_ch;//队友信息
	choice myChoice;//选择的坦克，以及是否确认；
	m_client client;//客户端

	bool retVal;
};


#endif // !_GAME_H_


