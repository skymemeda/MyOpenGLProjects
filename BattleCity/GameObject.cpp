#include "GameObject.h"


namespace tc
{
	GameObject::GameObject()
	{
		this->center_position = point<float>(100, 200);
		this->object_size = size<float>(32, 32);
		updateRect();
	}
	GameObject::~GameObject()
	{
	}
	void GameObject::setPosition(point<float>& _pos)
	{
		center_position = _pos;
		updateRect();
	}
	void GameObject::setPosition(float _x, float _y)
	{
		center_position.x = _x;
		center_position.y = _y;
		updateRect();
	}
	void GameObject::setSize(size<float>& _size)
	{
		object_size = _size;
		updateRect();
	}
	void GameObject::setSize(float _width, float _height)
	{
		object_size.w = _width;
		object_size.h = _height;
		updateRect();
	}
	void GameObject::updateRect()
	{
		object_rect.top = center_position.y + object_size.h / 2;
		object_rect.bottom = center_position.y - object_size.h / 2;
		object_rect.left = center_position.x - object_size.w / 2;
		object_rect.right = center_position.x + object_size.w / 2;
	}
}