#include "stdafx.h"
#include "GameManager.h"


Texture GameManager::m_gTex;
Render* GameManager::m_render;
BulletManager *bulletManager;
void GameManager::initGameManager(Render* _render)
{
	m_gTex = ph::TexPool::Get("system/texture/battlecity.png");
	m_render = _render;
}
GameManager::GameManager()
{
	bulletManager = new BulletManager();
	m_tank = new Tank();
	initbricks();	
}


GameManager::~GameManager()
{
	delete m_tank;
	delete bulletManager;
	delete[] m_bricks;
}
void GameManager::initbricks()
{
	//初始化墙块
	for (int bottomIndex = 0; bottomIndex < 15; bottomIndex++)
	{
		//下方
		tc::Brick *brick = new tc::Brick(bottomIndex * 32 + 16, 16);
		int endIndex = bottomIndex;
		m_bricks[endIndex] = brick;
	}
	for (int leftIndex = 0; leftIndex < 14; leftIndex++)
	{
		//左边
		tc::Brick *brick = new tc::Brick(16, (leftIndex + 1) * 32 + 16);
		int endIndex = leftIndex + 15;
		m_bricks[endIndex] = brick;
	}
	for (int topIndex = 0; topIndex < 14; topIndex++)
	{
		//上方
		tc::Brick *brick = new tc::Brick((topIndex + 1) * 32 + 16, 464);
		int endIndex = topIndex + 29;
		m_bricks[endIndex] = brick;
	}

	for (int rightIndex = 0; rightIndex < 14; rightIndex++)
	{
		//右边
		tc::Brick *brick = new tc::Brick(464, (rightIndex + 1) * 32 + 16);
		int endIndex = rightIndex + 43;
		m_bricks[endIndex] = brick;
	}
}
void GameManager::drawTank()
{
	m_tank->draw();
}
void GameManager::drawBricks()
{
	for (int index = 0; index < 56; index++)
	{
		m_bricks[index]->draw();
	}
}
void GameManager::drawBullet()
{
	if (bulletManager->len>0)
	{
		static long long preTick = 0;
		if (preTick == 0)
		{
			preTick = GetTickCount();
		}
		// 完成某5些工作的其他行程式 
		long long tick = GetTickCount();
		for (int index = 0; index<bulletManager->len; index++)
		{
			bool collideBrick = false;
			for (int brickIndex = 0; brickIndex<56; brickIndex++)
			{
				Brick *brick = m_bricks[brickIndex];
				if (bulletManager->bullets[index]->collide(brick))
				{
					collideBrick = true;
					bulletManager->deleteBullet(&(bulletManager->bullets[index]));
					break;
				}
			}
			if (!collideBrick)
			{
				rect<float> rect = bulletManager->bullets[index]->getBulletRect();
				bulletManager->bullets[index]->tick(tick - preTick);
			}
			//}
		}
		preTick = tick;
	}
	if (bulletManager->len > 0)
	{
		for (int index = 0; index < bulletManager->len; index++)
		{
			bulletManager->bullets[index]->draw();
		}
	}
}
void GameManager::draw()
{
	drawTank();
	drawBricks();
	drawBullet();
}

void GameManager::keyPressed(unsigned char _key)
{
	switch (_key)
	{
	case VK_UP:
	{
		m_tank->move(move_up);
		for (int index = 0; index < 56; index++)
		{
			if (m_tank->collide(m_bricks[index]))
			{
				m_tank->collideMoveBottom();
			}
		}
		break;
	}
	case VK_DOWN:
	{
		m_tank->move(move_down);
		for (int index = 0; index < 56; index++)
		{
			if (m_tank->collide(m_bricks[index]))
			{
				m_tank->collideMoveTop();
			}
		}
		break;
	}
	case VK_LEFT:
	{
		m_tank->move(move_left);
		for (int index = 0; index < 56; index++)
		{
			if (m_tank->collide(m_bricks[index]))
			{
				m_tank->collideMoveRight();
			}
		}
		break;
	}
	case VK_RIGHT:
	{
		m_tank->move(move_right);
		for (int index = 0; index < 56; index++)
		{
			if (m_tank->collide(m_bricks[index]))
			{
				m_tank->collideMoveLeft();
			}
		}
		break;
	}
	case VK_SPACE:
		m_tank->createBullet();
		break;
	default:
		break;
	}
}
void GameManager::update()
{
	m_tank->configTank();
	for (int index = 0; index < 56; index++)
	{
		m_bricks[index]->configBrick();
	}
	for (int bulletIndex = 0; bulletIndex<bulletManager->len; bulletIndex++)
	{
		bulletManager->bullets[bulletIndex]->configBullet();
	}
}
