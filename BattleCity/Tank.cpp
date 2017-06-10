#include "stdafx.h"
#include "Tank.h"
#include <res/TexPool.h>
#include "Bullet.h"
#include "BulletManager.h"
#include "GameManager.h"
namespace tc
{ 
	float Tank::m_picInfo[4][4]= {
		{ 64.0f / 512.0,96.0f / 512.0f,0,32.0f / 512.0f },
		{ 96.0f / 512.0f,128.0f / 512.0f,0.0f,32.0f / 512.0f },
		{ 0.0f,32.0f / 512.0f,0.0f,32.0f / 512.0f },
		{ 32.0f / 512.0f,64.0f / 512.0f,0.0f,32.0f / 512.0f }
	};

	void Tank::configTank()
	{
		RRC rrc;
		switch (tank_oriention)
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
		rrc.Color = 0x00ff00ff;
		ph::UIWidget::DefScissor( 0,1024,0,1024 );
		m_widget.Begin();
		m_widget.Build(rrc,GameManager::m_gTex, nullptr, 0);
		m_widget.End();
	}
	Tank::Tank()
	{
		m_color = 0x55ff55ff;
		tank_oriention = move_up;
		configTank();	
	}
	Tank::Tank(float _x, float _y, float _width, float _height, PhU32 _color)
	{
		center_position.x = _x;
		center_position.y = _y;
		object_size.w = _width;
		object_size.h = _height;
		m_color = _color;
		updateRect();
		configTank();
	}
	Tank::Tank(point<float> _point, size<float> _size, PhU32  _color)
	{
		center_position.x = _point.x;
		center_position.y = _point.y;
		object_size.w = _size.w;
		object_size.h = _size.h;
		m_color = _color;
		updateRect();
		configTank();
	}
	Tank::~Tank()
	{

	}
	void Tank::draw()
	{
		GameManager::m_render->Draw(&m_widget);
	}
	void Tank::collideMoveLeft()
	{
		center_position.x -= move_step;
		updateRect();
		configTank();
	}
	void Tank::collideMoveRight()
	{
		center_position.x += move_step;
		updateRect();
		configTank();
	}
	void Tank::collideMoveTop()
	{
		center_position.y += move_step;
		updateRect();
		configTank();
	}
	void Tank::collideMoveBottom()
	{
		center_position.y -= move_step;
		updateRect();
		configTank();
	}
	void Tank::moveRight()
	{
		if (tank_oriention == move_right)
		{
			center_position.x += move_step;
		}
		tank_oriention = move_right;
		updateRect();
		configTank();
	}
	void Tank::moveLeft()
	{
		if (tank_oriention == move_left)
		{
			center_position.x -= move_step;
		}
		tank_oriention = move_left;
		updateRect();
		configTank();
	}
	void Tank::moveBottom()
	{
		if (tank_oriention == move_down)
		{
			center_position.y -= move_step;
		}
		tank_oriention = move_down;
		updateRect();
		configTank();
	}
	void Tank::moveTop()
	{
		if (tank_oriention == move_up)
		{
			center_position.y += move_step;
		}
		tank_oriention = move_up;
		updateRect();
		configTank();
	}
	void Tank::move(move_type _mt)
	{
		switch (_mt)
		{
		case move_right:
		{
			moveRight();
			break;
		}
		case move_left:
		{
			moveLeft();
			break;
		}
		case move_down:
		{
			moveBottom();
			break;
		}
		case move_up:
		{
			moveTop();
			break;
		}
		default:
			break;
		}
	}
	bool Tank::isChangedOriention(move_type _oriention)
	{
		if (tank_oriention == _oriention)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	void Tank::setColor(PhU32 _color)
	{
		m_color = _color;
	}
	void Tank::createBullet()
	{
		point<float> bulletPoint;
		switch (tank_oriention)
		{
		case move_up:
			{
			    bulletPoint.set(object_rect.left + object_size.w / 2, object_rect.top);
			}
			break;
		case move_down:
			{
			    bulletPoint.set(object_rect.left + object_size.w / 2,object_rect.bottom);
			}
			break;
		case move_left:
			{
				bulletPoint.set(object_rect.left, object_rect.bottom + object_size.w / 2);
			}
			break;
		case move_right:
			{
				bulletPoint.set(object_rect.right,object_rect.bottom+object_size.w/2);
			}
			break;
		default:
			break;
		}

		Bullet *bullet = new Bullet(bulletPoint);
		bullet->setSpeedOriention(tank_oriention);
		if (bulletManager->len >= 5)
		{
			return;
		}
		int index = bulletManager->len;
		bulletManager->bullets[index] = bullet;
		bulletManager->len++;
	}
}

