#pragma once
#include "GameObject.h"
#include "TankObjectBase.h"
struct speed
{
	long speed_x;
	long speed_y;
};
namespace tc
{

	class Bullet :public GameObject
	{
	public:
		Bullet();
		Bullet(float _x, float _y, PhU32  _color);
		Bullet(point<float>_point, PhU32  _color);
		Bullet(float _x, float _y);
		Bullet(point<float>_point);
		~Bullet();
		speed getSpeed();
		rect<float> getBulletRect();
		void setSpeed(float _speedx, float _speedy);
		void setSpeedOriention(move_type type);
		void tick(long long _tick);
		void configBullet();
		void draw();
	private:
		PhU32  m_color;
		static float m_picInfo[4][4];
		UIWidget m_widget;
		move_type  m_oritention;
		speed  m_speed;
	};

}


