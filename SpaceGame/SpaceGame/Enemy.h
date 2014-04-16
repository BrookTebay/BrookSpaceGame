#ifndef _Enemy_H
#define _Enemy_H

#include "cD3DXTexture.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXFont.h"

class Enemy {

private:
	D3DXVECTOR3 enemyPosition;
	RECT enemyBounding;
	cD3DXTexture* enemyTexture;
	bool moveLeft,moveRight,moveUp,moveDown;

public:
	Enemy(cD3DXTexture* enemyTex, __int64 curT); //Construtor
	void Tick();//The update
	void Render(cD3DXSpriteMgr* spriteManager);//Draws the sprites
	void CreateBounding();//Creatues bounding box
	RECT ReturnBounds();//Returns bounding box
	void SetEnemySpawn(__int64 curT);//Sets spawn location

};


#endif
