#ifndef _RENDER_H_
#define _RENDER_H_

#include "coordinate.h"

namespace my_render {

	//ͼƬö����
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
		���ݳ���������Ⱦ���
		����ͼƬö����ͳ�������
		*/
		void rend_to_scene(images, position, rotation);

		/*
		������
		����һ��0��1��float��Ϊ�ٷֱ�
		int 0:��ɫ
		    1:��ɫ
			2:��ɫ
		����̹�˳�������
		*/
		void rend_life(float, int, position);

		/*
		��ȾС��ͼ
		int 0:��ɫ
		    1:��ɫ
			2:��ɫ
			3:��ɫ
			4:��Ⱦ�ײ�
		����̹�˳�������
		*/
		void rend_map(int,position);

		/*
		��һ���ߣ������ã�
		����������������
		*/
		void rend_line(position,position);

		//����ڳ���������
		position camera_position;

		//��ʼ��
		void init();
	};
}

//����Ⱦ��
extern my_render::render main_render;

#endif // !_RENDER_H_