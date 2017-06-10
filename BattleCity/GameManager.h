#pragma once

#include "Tank.h"
#include "Brick.h"
#include "TankObjectbase.h"
#include "BulletManager.h"
using namespace tc;
const int BrickCount = 56;
class GameManager
{
public:
	static Render *m_render;
	static Texture m_gTex;
	GameManager();
	~GameManager();
	static void initGameManager(Render* _render);
	void keyPressed(unsigned char _key);
	void draw();
	void update();
private:
	Tank *m_tank;
	Brick *m_bricks[56];
	void initbricks();
	void drawTank();
	void drawBricks();
	void drawBullet();
};

