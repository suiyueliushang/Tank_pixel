#ifndef _RENDER_H_
#define _RENDER_H_

#include "coordinate.h"

namespace my_render {

	//图片枚举类
	enum images {
		tank_blue,
		tank_red,
		tank_yellow,
		cannon_blue,
		cannon_red,
		cannon_yellow,
		tank_dead,
		cannon_dead,
		aim,
		bullet,
		background,
		wood,
		stone,
		wall,
		start
	};

	class render {
	public:
		render();

		/*
		根据场景坐标渲染物件
		传入图片枚举类和场景坐标
		*/
		void rend_to_scene(images, position, rotation);

		/*
		生命条
		传入一个0到1的float作为百分比
		int 0:绿色
		    1:蓝色
			2:红色
		传入坦克场景坐标
		*/
		void rend_life(float, int, position);

		/*
		渲染小地图
		int 0:绿色
		    1:蓝色
			2:红色
			3:灰色
			4:渲染底层
		传入坦克场景坐标
		*/
		void rend_map(int,position);

		/*
		画一条线（测试用）
		传入两个场景坐标
		*/
		void rend_line(position,position);

		//相机在场景下坐标
		position camera_position;

		//初始化
		void init();
	};
}

//主渲染器
extern my_render::render main_render;

#endif // !_RENDER_H_