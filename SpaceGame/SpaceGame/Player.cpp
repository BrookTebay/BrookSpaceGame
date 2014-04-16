#include "Player.h"

Player::Player(cD3DXTexture* playerTex){

	position = D3DXVECTOR3(400, 300, 0); //Sets the spawn location of the player
	playerTexture = playerTex;
}

//creates bounding box for player
void Player::Tick(){

	CreateBounding(); 

	if(position.x < 0){
		position.x = 0;
	}

	if(position.y < 0){
		position.y = 0;
	}

	if(position.x > 800 - playerTexture->getTWidth()){
		position.x = 800 - playerTexture->getTWidth();
	}

	if(position.y > 600- playerTexture->getTHeight()){
		position.y = 600- playerTexture->getTHeight();
	}

	

}

void Player::Render(cD3DXSpriteMgr* spriteManager){ //Draws player on screen

	spriteManager->drawSprite(playerTexture->getTexture(), NULL, NULL,&position, 0xFFFFFFFF);

}

void Player::PositionUp(int up){ //Moves player up

	position.y -=up;

}

void Player::PositionDown(int down){ //Moves player down
	position.y +=down;
}

void Player::PositionLeft(int left){ //Moves player left
	position.x -=left;
}

void Player::PositionRight(int right){ //Moves player right
	position.x +=right;
}

void Player::CreateBounding(){ //Creates bounding box for player
	SetRect(&playerBounding,position.x,position.y,position.x + playerTexture->getTWidth(),position.y + playerTexture->getTHeight());
}

RECT Player::ReturnBounds(){ //Returns bounding box for player
	return playerBounding;
}

D3DXVECTOR3 Player::GetPosition(){ //Returns position of the player
	return position;
}

