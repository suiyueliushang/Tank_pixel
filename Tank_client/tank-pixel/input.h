#ifndef _INPUT_H_
#define _INPUT_H_

#include "coordinate.h"
//原始输入，用于传输
class raw_input {
public:

	//调用ege相关接口获取输入
	void get_raw();

	int mouse_x=0;
	int mouse_y=0;

	//鼠标左右键是否按下
	bool left_is_down=0;
	bool right_is_down=0;

	//键盘方向键是否按下
	int up_and_down=0;
	int left_and_right=0;

	//预计算瞄准点
	position aim;
};

//输入控件处理函数原型
typedef bool(*check_func)(raw_input&,void*);

//输入控件（不渲染）
class menu_control {
public:
	menu_control();
	/*
	构造函数
	提供左上角点和右下角点和一个处理函数
	*/
	menu_control(position,position,check_func);
	/*
	执行控件处理
	传入原始输入和相关参数
	*/
	bool check(raw_input&,void*);

private:
	position left_top;
	position right_buttom;
	check_func m_check;
};

/*
坦克输入控件
检查时另行传入一个坦克指针
返回true则发射一颗子弹
*/
extern menu_control tank_input;

/*
镜头左移控件
另行传入dt的指针
*/
extern menu_control leftbar;

/*
镜头右移控件
另行传入dt的指针
*/
extern menu_control rightbar;

/*
镜头上移控件
另行传入dt的指针
*/
extern menu_control topbar;

/*
镜头下移控件
另行传入dt的指针
*/
extern menu_control buttombar;

/*
小地图控件
*/
extern menu_control map;

/*
开始游戏控件
点击则连接服务器，开始匹配
*/
extern menu_control playing;

/*
开始游戏控件
*/
extern menu_control start;


/*
选择坦克控件
*/
extern menu_control choose1;
extern menu_control choose2;
extern menu_control choose3;

/*
选择坦克确定控件
*/
extern menu_control confirm;


#endif // !_INPUT_H_