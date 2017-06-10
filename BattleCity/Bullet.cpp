#include "stdafx.h"
#include "Bullet.h"
#include <stdio.h>
#include "GameManager.h"
const int bulletSpeed = 150;
namespace tc
{
	float Bullet::m_picInfo[4][4] = {
		{160.0/512.0,170.0/512.0,0.0,10.0/512.0},
		{170.0/512.0,180.0/512.0,0.0,10.0/512.0},
		{160.0 / 512.0,170.0 / 512.0,10.0/512.0,20.0/512.0},
		{160.0 / 512.0,170.0 / 512.0,20.0/512.0,30.0/512.0}
	};
	void Bullet::configBullet()
	{
		RRC rrc;
		switch (m_oritention)
		{
		case move_up:
		{
			rrc.TcXMin = m_picInfo[0][0];
			rrc.TcXMax = m_picInfo[0][1];
			rrc.TcYMin = m_picInfo[0][2];
			rrc.TcYMax = m_picInfo[0][3];
		}
		break;
		case move_down:
		{
			rrc.TcXMin = m_picInfo[1][0];
			rrc.TcXMax = m_picInfo[1][1];
			rrc.TcYMin = m_picInfo[1][2];
			rrc.TcYMax = m_picInfo[1][3];
		}
		break;
		case move_right:
		{
			rrc.TcXMin = m_picInfo[3][0];
			rrc.TcXMax = m_picInfo[3][1];
			rrc.TcYMin = m_picInfo[3][2];
			rrc.TcYMax = m_picInfo[3][3];
		}
		break;
		case move_left:
		{
			rrc.TcXMin = m_picInfo[2][0];
			rrc.TcXMax = m_picInfo[2][1];
			rrc.TcYMin = m_picInfo[2][2];
			rrc.TcYMax = m_picInfo[2][3];
		}
		break;
		default:
			break;
		}
		rrc.PosXMin = object_rect.left;
		rrc.PosXMax = object_rect.right;
		rrc.PosYMin = object_rect.bottom;
		rrc.PosYMax = object_rect.top;

		rrc.MtcXMin = rrc.MtcYMin = 0.0f;
		rrc.MtcXMax = rrc.MtcYMax = 1.0f;
		rrc.Gray = 0.0f;
		rrc.Color = 0xffffffff;
		m_widget.Begin();
		m_widget.Build(rrc,GameManager::m_gTex, nullptr, 0);
		m_widget.End();
	}
	Bullet::Bullet()
	{
		object_size.w = 10;
		object_size.h = 10;
		m_color = 0x55ff55ff;
		center_position = point<float>(200, 100);
		m_speed.speed_x = 20;
		m_speed.speed_y = 0;
		updateRect();
	}
	Bullet::Bullet(float _x, float _y, PhU32 _color)
	{
		center_position.x = _x;
		center_position.y = _y;
		m_color = _color;
		object_size.w = 10;
		object_size.h = 10;
		m_speed.speed_x = 0;
		m_speed.speed_y = 0;
		updateRect();
	}
	Bullet::Bullet(point<float>_point, PhU32 _color)
	{
		center_position.x = _point.x;
		center_position.y = _point.y;
		m_color = _color;
		object_size.w = 10;
		object_size.h = 10;
		m_speed.speed_x = 0;
		m_speed.speed_y = 0;
		updateRect();
	}
	Bullet::Bullet(float _x, float _y)
	{
		center_position.x = _x;
		center_position.y = _y;
		m_color = 0x55ff55ff;
		object_size.w = 8;
		object_size.h = 8;
		m_speed.speed_x = 0;
		m_speed.speed_y = 0;
		updateRect();
	}
	Bullet::Bullet(point<float>_point)
	{
		center_position.x = _point.x;
		center_position.y = _point.y;
		m_color = 0x55ff55ff;
		object_size.w = 8;
		object_size.h = 8;
		m_speed.speed_x = 0;
		m_speed.speed_y = 0;
		updateRect();
	}
	speed Bullet::getSpeed()
	{
		return m_speed;
	}
	rect<float> Bullet::getBulletRect()
	{
		return object_rect;
	}
	void Bullet::setSpeedOriention(move_type type)
	{
		m_oritention = type;
		switch (type) {
		case move_up:
		{
			m_speed.speed_x = 0;
			m_speed.speed_y = bulletSpeed;
		}
		break;
		case move_down:
		{
			m_speed.speed_x = 0;
			m_speed.speed_y = -bulletSpeed;
		}
		break;
		case move_left:
		{
			m_speed.speed_x = -bulletSpeed;
			m_speed.speed_y = 0;
		}
		break;
		case move_right:
		{
			m_speed.speed_x = bulletSpeed;
			m_speed.speed_y = 0;
		}
		break;
		};
		configBullet();

	}
	void Bullet::setSpeed(float _speedx, float _speedy)
	{
		m_speed.speed_x = _speedx;
		m_speed.speed_y = _speedy;
	}
	void Bullet::tick(long long _tick)
	{
		float x = center_position.x + (float)m_speed.speed_x*(float)_tick / 1000.0f;
		float y = center_position.y + (float)m_speed.speed_y*(float)_tick / 1000.0f;
		setPosition(x, y);
		configBullet();
	}
	Bullet::~Bullet()
	{
	}
	void Bullet::draw()
	{
		GameManager::m_render->Draw(&m_widget);
	}
}

