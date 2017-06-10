#pragma once
#include "GameObject.h"
#include "TypeDef.h"
#include "GameDef.h"
#include <string>
#include "TankObjectBase.h"
namespace tc
{
	const int move_step = 5;
	class Tank :public GameObject
	{
	public:
		Tank();
		Tank(float _x, float _y, float _width, float _height, PhU32 _color);
		Tank(point<float> _point, size<float> _size, PhU32 _color);
		~Tank();
		void configTank();
		void draw();
		void move(move_type _mt);
		void setColor(PhU32 _color);
		void createBullet();
		bool isChangedOriention(move_type _oriention);
		void collideMoveLeft();
		void collideMoveRight();
		void collideMoveTop();
		void collideMoveBottom();
	private:
		PhU32  m_color;
		move_type  tank_oriention;
		static float m_picInfo[4][4];
		UIWidget m_widget;
		void moveRight();
		void moveLeft();
		void moveBottom();
		void moveTop();
		

	};
}

