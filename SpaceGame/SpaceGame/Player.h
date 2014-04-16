#ifndef _PLAYER_H
#define _PLAYER_H

#include "cD3DXTexture.h"
#include "cD3DXSpriteMgr.h"



class Player {

private:
	D3DXVECTOR3 position;
	RECT playerBounding;
	cD3DXTexture* playerTexture;

public:
	Player(cD3DXTexture* playerTex); //Constructor
	void Tick();// Update
	void Render(cD3DXSpriteMgr* spriteManager); //Draws the sprite
	void PositionUp(int up); //Moves player up
	void PositionDown(int down); //Moves player down
	void PositionLeft(int left); //Moves player left
	void PositionRight(int right); //Moves player right
	void CreateBounding(); //Creates the players bounding box
	RECT ReturnBounds(); //Return the players bounding box
	D3DXVECTOR3 GetPosition(); //Gets the current position
	
};



#endif