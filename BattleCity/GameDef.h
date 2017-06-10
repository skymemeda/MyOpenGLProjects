#pragma once
#ifndef __GAME_DEF_H__
#define __GAME_DEF_H__

namespace tc
{
	template <class T>
	class point
	{
	public:
		T x;
		T y;
		point()
		{
			x = 0;
			y = 0;
		}
		point(T _x, T _y)
		{
			x = _x;
			y = _y;
		}
		
	};
	template <class T>
	class size
	{
	public:
		T width;
		T height;
		size()
		{
			width = 0;
			height = 0;
		}
		size(T _width, T _height)
		{
			width = _width;
			height = _height;
		}
	};
	template <class T>
	class rect
	{
	public:
		T left;
		T right;
		T bottom;
		T top;
		rect(T _left, T _right, T _bottom, T _top)
		{
			left = _left;
			right = _right;
			bottom = _bottom;
			top = _top;
		}
		rect()
		{
			left = 0;
			right = 0;
			bottom = 0;
			top = 0;
		}
		//           void operator= (rect<T>& _rc)
		//           {
		//               left = _rc.left;
		//               bottom = _rc.bottom;
		//               top = _rc.top;
		//               right = _rc.right;
		//           }
		bool hit_test(rect<T>& _rc)
		{
			if (left >= _rc.right) return false;
			if (bottom <= _rc.top) return false;
			if (right <= _rc.left) return false;
			if (top >= _rc.bottom) return false;
			return true;
		}
		bool hit_test(point<T>& _pt)
		{
			if (_pt.x < left) return false;
			if (_pt.x > right) return false;
			if (_pt.y > top) return false;
			if (_pt.y < bottom) return false;
			return true;
		}
		bool hit_test_border(rect<T>& _rc)
		{
			if (top <= _rc.top) return true;
			if (bottom >= _rc.bottom) return true;
			if (left <= _rc.left) return true;
			if (right >= _rc.right) return true;
			return false;
		}
	};
	class circle
	{
	public:
		circle()
		{
			m_center = point<float>(0, 0);
			m_radius = 0;
		}
		circle(point<float> _center, float _radius)
		{
			m_center.x = _center.x;
			m_center.y = _center.y;
			m_radius = _radius;
		}
		circle(float _x, float _y, float _radius)
		{
			m_center.x = _x;
			m_center.y = _y;
			m_radius = _radius;
		}
		point<float> m_center;
		float m_radius;
	};
	enum move_type
	{
		move_left = 0,
		move_right,
		move_down,
		move_up
	};
}

#endif // __GAME_DEF_H__

