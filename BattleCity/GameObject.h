#pragma once
#include "TypeDef.h"
using namespace ph;
namespace tc
{

	class GameObject
	{
	public:
		GameObject();
		~GameObject();
		void setPosition(point<float>& _pos);
		void setSize(size<float>& _size);
		void setPosition(float _x, float _y);
		void setSize(float _width, float _height);
		
		bool collide(rect<float>& _rc)
		{
			return object_rect.hit_test(_rc);
		}
		bool collide(point<float>& _pt)
		{
			return object_rect.hit_test(_pt);
		}
		bool collide(GameObject* _go)
		{
			return this->collide(_go->object_rect);
		}
	protected:
		point<float>   center_position;
		size<float>    object_size;
		rect<float>    object_rect;
		void updateRect();
	};

}

