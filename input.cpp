#include "input.h"
#include <graphics.h>
#include "render.h"

/*
author: forcyan
*/
void raw_input::get_raw()
{
	/*
	加一个指向当前控制的应用
	*/
	while (kbmsg())
	{
		key_msg key_message = getkey();
		switch (key_message.key)
		{
		case 38://方向键上
			if (key_message.msg == 1)
				up_and_down = 1;
			else if (key_message.msg == 2)
				up_and_down = 0;
			break;
		case 40://方向键下
			if (key_message.msg == 1)
				up_and_down = -1;
			else if (key_message.msg == 2)
				up_and_down = 0;
			break;
		case 37://方向键左
			if (key_message.msg == 1)
				left_and_right = 1;
			else if (key_message.msg == 2)
				left_and_right = 0;
			break;
		case 39://方向键右
			if (key_message.msg == 1)
				left_and_right = -1;
			else if (key_message.msg == 2)
				left_and_right = 0;
			break;
		}
	}
	/*
	左键控制目标点
	*/
	while (mousemsg())
	{
		mouse_msg mouse_messsage = getmouse();
		if (mouse_messsage.is_left()) {
			if (mouse_messsage.is_down()) {
				left_is_down = true;
			}
			if (mouse_messsage.is_up()) {
				left_is_down = false;
			}
		}
		if (mouse_messsage.is_right()) {
			if (mouse_messsage.is_down()) {
				right_is_down = true;
			}
			if (mouse_messsage.is_up()) {
				right_is_down = false;
			}
		}
	}
	mousepos(&mouse_x, &mouse_y);
	aim = position(mouse_x, mouse_y) + main_render.camera_position - position(540, 360);
}

menu_control::menu_control(position lt, position rb, check_func f)
{
	left_top = lt;
	right_buttom = rb;
	m_check = f;
}

/*
author: K024
*/
bool menu_control::check(raw_input &r, void *p)
{
	//检测鼠标是否在控件范围
	if (r.mouse_x < left_top.x() || r.mouse_x >= right_buttom.x() ||
		r.mouse_y < left_top.y() || r.mouse_y >= right_buttom.y())
		return false;
	return (*m_check)(r, p);
}


#include "tank.h"

/*
author: forcyan
*/
bool tank_input_func(raw_input&r, void*p) {
	tank*tp = (tank*)p;
	if (r.left_is_down)
		tp->set_aim(r.aim);
	tp->set_lar(r.left_and_right);
	tp->set_uad(r.up_and_down);
	if (r.right_is_down)
		if (tp->shoot())return true;
	return false;
}

menu_control tank_input(position(0, 0), position(1080, 720), tank_input_func);



/*
author: K024
*/
bool leftbar_func(raw_input& r, void*p) {
	main_render.camera_position -= position((100 - r.mouse_x) * 3 * *(float*)p, 0);
	if (main_render.camera_position.x() < -1000) {
		main_render.camera_position.x(-1000);
	}
	return true;
}

menu_control leftbar(position(0, 0), position(100, 520), leftbar_func);





/*
author: K024
*/
bool topbar_func(raw_input& r, void*p) {
	main_render.camera_position -= position(0, (100 - r.mouse_y) * 3 * *(float*)p);
	if (main_render.camera_position.y() < -1000) {
		main_render.camera_position.y(-1000);
	}
	return true;
}

menu_control topbar(position(0, 0), position(1080, 100), topbar_func);





/*
author: K024
*/
bool rightbar_func(raw_input& r, void*p) {
	main_render.camera_position += position((r.mouse_x - 980) * 3 * *(float*)p, 0);
	if (main_render.camera_position.x() > 1000) {
		main_render.camera_position.x(1000);
	}
	return true;
}

menu_control rightbar(position(980, 0), position(1080, 720), rightbar_func);






/*
author: K024
*/
bool buttombar_func(raw_input& r, void*p) {
	main_render.camera_position += position(0, (r.mouse_y - 620) * 3 * *(float*)p);
	if (main_render.camera_position.y() > 1000) {
		main_render.camera_position.y(1000);
	}
	return true;
}

menu_control buttombar(position(100, 620), position(1080, 720), buttombar_func);





/*
author: K024
*/
bool map_func(raw_input& r, void*p) {
	//if (!r.left_is_down)
		return false;
	main_render.camera_position = position((r.mouse_x - 100) * 10, (r.mouse_y - 620) * 10);
	return true;
}

menu_control map(position(0, 520), position(200, 720), map_func);



bool start_func(raw_input& r, void*p) {
	if (r.left_is_down)
	{
		return true;
	}
	return false;
}

menu_control start(position(400, 260), position(680, 460), start_func);


bool choose_func(raw_input& r,void*)
{
	if (r.left_is_down)
	{
		return true;
	}
	return false;
}

menu_control choose1(position(100, 100), position(150, 150), choose_func);
menu_control choose2(position(200, 200), position(250, 250), choose_func);
menu_control choose3(position(300, 300), position(350, 350), choose_func);

bool confirm_func(raw_input& r, void*)
{
	if (r.left_is_down)
	{
		return true;
	}
	return false;
}

menu_control confirm(position(500, 500), position(600, 600), confirm_func);