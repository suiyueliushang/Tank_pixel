#ifndef _GAME_H_
#define _GAME_H_

#include "scene.h"
#include"Server.h"

/*
game.h
��Ϸ��

��Ϸ��ڶ���
��Ϸ��������
��Ϸ��ѭ��


*/
class game 
{
public:
	/*
	����������Դ�ļ�
	*/
	game();
	~game(); 

	/*
	��Ϸ��ѭ��
	���ö�Ӧ������update��render
	���Ƴ����л�
	����֡��
	*/
	void game_cycle();

private:

	gameScene m_gameScene;
};


#endif // !_GAME_H_