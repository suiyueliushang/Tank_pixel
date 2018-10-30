#include "render.h"


#include <graphics.h>


using namespace my_render;

render main_render;

//对应枚举类顺序的图片地址
const char* imgurls[] = {
	"./resources/tank_blue.bmp",
	"./resources/tank_red.bmp",
	"./resources/tank_yellow.bmp",
	"./resources/cannon_blue.bmp",
	"./resources/cannon_red.bmp",
	"./resources/cannon_yellow.bmp",
	"./resources/tank_dead.png",
	"./resources/cannon_dead.png",
	"./resources/aim.bmp",
	"./resources/bullet.bmp",
	"./resources/background.png",
	"./resources/wood.png",
	"./resources/stone.png",
	"./resources/wall.png",
	"./resources/start.jpg"
};

//图片指针
PIMAGE pimgs[sizeof(imgurls)/sizeof(char*)];

render::render()
{
}

/*
author: forcyan
*/
void render::rend_to_scene(images img, position s_position, rotation s_rotation)
{
	s_position -= camera_position;//转为相机坐标
	s_position += position(540, 360);//转为屏幕坐标，（540，360）为相机零点在屏幕坐标的位置
	putimage_rotate(nullptr, pimgs[img], s_position.x(), s_position.y(), 0.5f, 0.5f, s_rotation.r(), 1);
}

/*
author: K024
*/
void my_render::render::rend_life(float percent, int type, position po)
{
	po -= camera_position;
	po += position(540, 360);
	setfillcolor(0x50000000);
	bar(po.x() - 25, po.y() - 30, po.x() + 25, po.y() - 25);
	switch (type) {
	case 0:
		setfillcolor(0x33ff46); 
		break;
	case 1:
		setfillcolor(0x1ed1ff);
		break;
	case 2:
		setfillcolor(0xff1e1e);
		break;
	}
	bar(po.x() - 25, po.y() - 30, po.x() - 25 + 50 * percent, po.y() - 25);
	setfillcolor(0x50555555);
	rectangle(po.x() - 25, po.y() - 30, po.x() + 25, po.y() - 25);

}

void my_render::render::rend_map(int c, position p)
{
	switch (c) {
	case 4:
		setfillcolor(0x517e4a);
		bar(0, 520, 200, 720);
		return;
		break;
	case 0:
		setfillcolor(0x33ff46);
		break;
	case 1:
		setfillcolor(0x1ed1ff);
		break;
	case 2:
		setfillcolor(0xff1e1e);
		break;
	case 3:
		setfillcolor(0x333333);
		break;
	}
	fillellipse(p.x() / 10 + 100, p.y() / 10 + 620, 4,4);
}

void my_render::render::rend_line(position p, position q)
{
	return;
	p -= camera_position;
	p += position(540, 360);
	q -= camera_position;
	q += position(540, 360);
	line(p.x(), p.y(), q.x(), q.y());
}


void my_render::render::init()
{
	for (int i = 0; i < sizeof(imgurls) / sizeof(char*); i++) {
		pimgs[i] = newimage();
		getimage(pimgs[i], imgurls[i]);
	}
}

