#pragma once
#include "GameObject.h"
#include "TankObjectBase.h"
namespace tc
{

	class Brick : public GameObject
	{
	public:
		Brick();
		Brick(float _x, float _y, float _width, float _height);
		Brick(point<float> _point, size<float> _size);
		Brick(float _x, float _y);
		Brick(point<float>_point);
		void configBrick();
		~Brick();
		void draw();

	private:
		UIWidget   m_widget;
		static float m_picInfo[4];

	};

}

