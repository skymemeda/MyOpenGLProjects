#include "stdafx.h"
#include "Brick.h"
#include "Gamemanager.h"

namespace tc
{
	float Brick::m_picInfo[4] = {128.0/512.0,160.0/512.0,0.0,32.0/512.0};
	void Brick::configBrick()
	{
		RRC rrc;
		rrc.TcXMin = m_picInfo[0];
		rrc.TcXMax = m_picInfo[1];
		rrc.TcYMin = m_picInfo[2];
		rrc.TcYMax = m_picInfo[3];
		rrc.PosXMin = object_rect.left;
		rrc.PosXMax = object_rect.right;
		rrc.PosYMin = object_rect.bottom;
		rrc.PosYMax = object_rect.top;

		rrc.MtcXMin = rrc.MtcYMin = 1.0f;
		rrc.MtcXMax = rrc.MtcYMax = 1.0f;
		rrc.Gray = 0.0f;
		rrc.Color = 0xffffffff;
		m_widget.Begin();
		m_widget.Build(rrc,GameManager::m_gTex, nullptr, 0);
		m_widget.End();
	}
	Brick::Brick()
	{
		center_position.x = 0;
		center_position.y = 0;
		updateRect();
		configBrick();
	}
	Brick::Brick(float _x, float _y, float _width, float _height)
	{
		center_position.x = _x;
		center_position.y = _y;
		object_size.w = _width;
		object_size.h = _height;
		updateRect();
		configBrick();
	}
	Brick::Brick(point<float> _point, size<float> _size)
	{
		center_position.x = _point.x;
		center_position.y = _point.y;
		object_size.w = _size.w;
		object_size.h = _size.h;
		updateRect();
		configBrick();
	}
	Brick::Brick(float _x, float _y)
	{
		center_position.x = _x;
		center_position.y = _y;
		object_size.w = 32;
		object_size.h = 32;
		updateRect();
		configBrick();
	}
	Brick::Brick(point<float>_point)
	{
		center_position.x = _point.x;
		center_position.y = _point.y;
		object_size.w = 32;
		object_size.h = 32;
		updateRect();
		configBrick();
	}
	Brick::~Brick()
	{
	}
	void Brick::draw()
	{
		GameManager::m_render->Draw(&m_widget);
	}
}