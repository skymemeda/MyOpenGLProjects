#pragma once
#include "Bullet.h"
using namespace tc;
struct BulletManager
{
	Bullet  **bullets;
	int       len;
	BulletManager()
	{
		bullets = new Bullet*[5];
		len = 0;
	}
	void deleteBullet(Bullet ** bullet)
	{
		for (int i = 0; i<len; i++)
		{
			if (*bullet == bullets[i])
			{
				*bullet = NULL;
				delete *bullet;
				for (int j = i + 1; j<len; j++)
				{
					bullets[j - 1] = bullets[j];
				}
				len--;
				break;
			}
		}
	}
};
extern BulletManager *bulletManager;
