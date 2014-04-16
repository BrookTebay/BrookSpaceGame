#include "Bullets.h"

Bullets::Bullets(cD3DXTexture* bulletTex, D3DXVECTOR3 playerPosition){

	bulletPosition = playerPosition;
	bulletTexture = bulletTex;

}

void Bullets::ShootBullet(){

	bulletPosition.y-=15;

	CreateBounding();

}

void Bullets::CreateBounding(){

	SetRect(&bulletBound, bulletPosition.x, bulletPosition.y, bulletPosition.x + bulletTexture->getTWidth(), bulletPosition.y + bulletTexture->getTHeight());

}

RECT Bullets::GetBounds(){

	return bulletBound;
	
}

void Bullets::RenderBullet(cD3DXSpriteMgr* SpriteManger){

	SpriteManger->drawSprite(bulletTexture->getTexture(),NULL,NULL,&bulletPosition,0xFFFFFFFF);

}