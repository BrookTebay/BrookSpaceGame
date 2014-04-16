#include "Enemy.h"

Enemy::Enemy(cD3DXTexture* enemyTex, __int64 curT){ //Initilises booleon so ships can move correctly

	moveRight = false;
	moveLeft = false;
	moveUp= false;
	moveDown = false;




	SetEnemySpawn(curT);
	enemyTexture = enemyTex;

}

void Enemy::Tick(){ //Updates enemy movement

	CreateBounding();

	if(moveUp) //Moves the enemy up
		enemyPosition.y += 4;

	else if(moveDown) //Moves the enemy down
		enemyPosition.y -= 4;

	else if(moveLeft) //Moves the enemy left
		enemyPosition.x -= 4;

	else //Moves the enemy right
		enemyPosition.x += 4;
	

}

void Enemy::Render(cD3DXSpriteMgr* spriteManager){ //Draws the sprites

	spriteManager->drawSprite(enemyTexture->getTexture(), NULL, NULL, &enemyPosition, 0xFFFFFFFF);
}

void Enemy::CreateBounding(){ //Creates the bounding box for collsion
	SetRect(&enemyBounding,enemyPosition.x,enemyPosition.y,enemyPosition.x + enemyTexture->getTWidth(),enemyPosition.y + enemyTexture->getTHeight());
}

RECT Enemy::ReturnBounds(){ //Returns the position of the enemy bounding box
	return enemyBounding;
}

void Enemy::SetEnemySpawn(__int64 curT){ 



	
	srand((unsigned int)time(NULL) * ((int)curT));

	int r = 1+(rand() % 4); //Spawns enemies in random position outside of the screen



	
	if(r==1){

		enemyPosition = D3DXVECTOR3(-100, 1+(rand() % 600),0); //If left of screen turns moveRight to true
		moveRight = true;

	}else if(r==2){

		enemyPosition=D3DXVECTOR3(900, 1+(rand()%600), 0); //If right of screen turns moveLeft to true
		moveLeft = true;

	}else if(r==3){

		enemyPosition=D3DXVECTOR3(1+(rand()%800), 700, 0); //If Above screen turns moveDown to true
		moveDown = true;

	}else{

		enemyPosition=D3DXVECTOR3(1+(rand()%800), -100, 0); //If below screen turns moveUp to true
		moveUp= true;

	}
	

}





