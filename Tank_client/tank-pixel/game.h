#ifndef _GAME_H_
#define _GAME_H_

#include"scene.h"
#include"input.h"
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
	menuScene m_menuScene;
	gameScene m_gameScene;
private:
	friend_choice f_ch;//������Ϣ
	choice myChoice;//ѡ���̹�ˣ��Լ��Ƿ�ȷ�ϣ�
	m_client client;//�ͻ���

	bool retVal;
};


#endif // !_GAME_H_


