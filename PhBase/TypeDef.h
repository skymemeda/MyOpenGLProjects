#pragma once
#include <stdint.h>

typedef uint8_t			PhU8;
typedef uint16_t		PhU16;
typedef uint32_t		PhU32;
typedef uint64_t		PhU64;
typedef size_t			PhSizeT;

typedef int8_t			PhI8;
typedef int16_t			PhI16;
typedef int32_t			PhI32;
typedef int64_t			PhI64;

namespace ph
{
	template < class T>
	struct point
	{
		T x;
		T y;
		point()
		{
			x = y = 0;
		}
		point(T _x, T _y) 
		{
			x = _x; y = _y;
		}
		void set(T _x, T _y)
		{
			x = _x; y = _y;
		}
	};

	template < class T>
	struct size
	{
		T w;
		T h;
		size()
		{
			w = h = 0;
		}
		size(T _w, T _h)
		{
			w = _w;
			h = _h;
		}
		void set(T _w, T _h)
		{
			w = _w; h = _h;
		}
	};

	template < class T>
	struct rect
	{
		T left; T right;
		T bottom; T top;
		rect()
		{
			left = right = bottom = top = 0;
		}
		rect(T _l, T _r, T _b, T _t ) :( left)_l, (right)_r, ( bottom)_b, ( top)_t
		{}
		void set(T _l, T _r, T _b, T _t)
		{
			left = _l;
			right = _r;
			bottom = _b;
			top = _t;
		}
		bool hit_test(rect<T>& _rc)
		{
			if (left >= _rc.right) return false;
			if (bottom >= _rc.top) return false;
			if (right <= _rc.left) return false;
			if (top <= _rc.bottom) return false;
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
			if (top >= _rc.top) return true;
			if (bottom <= _rc.bottom) return true;
			if (left <= _rc.left) return true;
			if (right >= _rc.right) return true;
			return false;
		}
	};

	template < class T >
	struct area
	{
		T x;T y;
		T w;T h;
		area()
		{
			x = y = w = h = 0;
		}
		area(T _x, T _y, T _w, T _h):( x)_x, (y)_y, (w)_w,(h)_h
		{}
		void set(T _x, T _y, T _w, T _h)
		{   
			x = _x;
			y = _y;
			w = _w;
			h = _h;
		}
	};

	struct vec4
	{
		float x, y, z, w;
		vec4()
		{
			x = y = z = w = 0.0f;
		}
		vec4(float _x, float _y, float _z, float _w)
		{
			x = _x; y = _y; z = _z; w = _w;
		}
	};

	struct vec3
	{
		float x, y, z;
		vec3()
		{
			x = y = z = 0.0f;
		}
		vec3(float _x, float _y, float _z)
		{
			x = _x; y = _y; z = _z;
		}
	};

	struct vec2
	{
		float x, y;
		vec2()
		{
			x = y = 0.0f;
		}
		vec2(float _x, float _y)
		{
			x = _x; y = _y;
		}
	};
	enum move_type
	{
		move_left = 0,
		move_right,
		move_down,
		move_up
	};

}
