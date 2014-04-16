#ifndef _ENEMYSPAWNER_H
#define _ENEMYSPAWNER_H

#include "GameConstants.h"
#include "Enemy.h"
#include "cD3DManager.h"
#include "Player.h"

class EnemySpawner{

private:

	__int64 freq;
	__int64 curT;
	__int64 prevT;
	float sec;
	bool end;

	

public:

	EnemySpawner();//Constuctor
	
	void Spawner(cD3DManager* m); //To pass the manager in
	void DrawEnemies(cD3DXSpriteMgr* s);//Draws on screen
	void Tick(Player* player);//Update method
	vector<Enemy*> enemies;
	vector<Enemy*>::iterator iter;
	bool End(); //Returns true if the game is to end
	void Reset();//Turns reset to false
};
#endif