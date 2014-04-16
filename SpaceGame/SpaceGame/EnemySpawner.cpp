#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(){ //Initilises the spawner class

	freq=0;
	curT=0;
	prevT=0;
	sec=0;
	end = false;
	

	QueryPerformanceFrequency((LARGE_INTEGER*)&freq); 
	QueryPerformanceCounter((LARGE_INTEGER*)&prevT);

	sec = 1.0f/(float)freq;
}

void EnemySpawner::Spawner(cD3DManager* m){ 

	QueryPerformanceCounter((LARGE_INTEGER*)&curT); 

	//If 0.4seconds is passed spawn a new enemy
	if(((curT-prevT) * sec) > 0.4f){
		enemies.push_back(new Enemy(new cD3DXTexture(m->getTheD3DDevice(), "Images\\Enemy.png"), curT));
		prevT = curT;
	}


}

void EnemySpawner::Tick(Player* player){

	RECT tempRect;

	for(iter=enemies.begin();iter!=enemies.end();++iter){ //Looping through enemy list

		(*iter)->Tick(); //Updates the enemy
	
		if(IntersectRect(&tempRect,&(*iter)->ReturnBounds(),&player->ReturnBounds())){ //Checks for collision betweene enemy and play
			end = true;		
		}


					

	}

}

//Drawing the enemy
void EnemySpawner::DrawEnemies(cD3DXSpriteMgr* s){ 

	for(iter=enemies.begin();iter!=enemies.end();iter++){

		(*iter)->Render(s);

	}

}

//Turns true if game is meant to end
bool EnemySpawner:: End(){

	return end;
}

//Turns end to false when resetting the game
void EnemySpawner:: Reset(){

	end = false;

}


