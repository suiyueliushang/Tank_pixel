#ifndef _INPUT_H_
#define _INPUT_H_

#include "coordinate.h"
//ԭʼ���룬���ڴ���
class raw_input {
public:

	//����ege��ؽӿڻ�ȡ����
	void get_raw();

	int mouse_x=0;
	int mouse_y=0;

	//������Ҽ��Ƿ���
	bool left_is_down=0;
	bool right_is_down=0;

	//���̷�����Ƿ���
	int up_and_down=0;
	int left_and_right=0;

	//Ԥ������׼��
	position aim;
};

//����ؼ�������ԭ��
typedef bool(*check_func)(raw_input&,void*);

//����ؼ�������Ⱦ��
class menu_control {
public:
	menu_control();
	/*
	���캯��
	�ṩ���Ͻǵ�����½ǵ��һ��������
	*/
	menu_control(position,position,check_func);
	/*
	ִ�пؼ�����
	����ԭʼ�������ز���
	*/
	bool check(raw_input&,void*);

private:
	position left_top;
	position right_buttom;
	check_func m_check;
};

/*
̹������ؼ�
���ʱ���д���һ��̹��ָ��
����true����һ���ӵ�
*/
extern menu_control tank_input;

/*
��ͷ���ƿؼ�
���д���dt��ָ��
*/
extern menu_control leftbar;

/*
��ͷ���ƿؼ�
���д���dt��ָ��
*/
extern menu_control rightbar;

/*
��ͷ���ƿؼ�
���д���dt��ָ��
*/
extern menu_control topbar;

/*
��ͷ���ƿؼ�
���д���dt��ָ��
*/
extern menu_control buttombar;

/*
С��ͼ�ؼ�
*/
extern menu_control map;

/*
��ʼ��Ϸ�ؼ�
��������ӷ���������ʼƥ��
*/
extern menu_control playing;

/*
��ʼ��Ϸ�ؼ�
*/
extern menu_control start;


/*
ѡ��̹�˿ؼ�
*/
extern menu_control choose1;
extern menu_control choose2;
extern menu_control choose3;

/*
ѡ��̹��ȷ���ؼ�
*/
extern menu_control confirm;


#endif // !_INPUT_H_