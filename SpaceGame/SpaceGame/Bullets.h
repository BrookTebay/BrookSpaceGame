#include "cD3DXTexture.h"
#include "GameConstants.h"
#include "cD3DXSpriteMgr.h"

class Bullets{


private:

	D3DXVECTOR3 bulletPosition;
	cD3DXTexture* bulletTexture;
	RECT bulletBound;

public:

	Bullets(cD3DXTexture* bulletTex, D3DXVECTOR3 playerPosition);

	void ShootBullet();
	void CreateBounding();
	RECT GetBounds();
	void RenderBullet(cD3DXSpriteMgr* SpriteManger);


};
