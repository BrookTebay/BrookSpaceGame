
/*
=================
main.cpp
Main entry point for the Card application
=================
*/

#include "GameConstants.h"
#include "GameResources.h"
#include "cD3DManager.h"
#include "cD3DXSpriteMgr.h"
#include "cD3DXTexture.h"
#include "cBalloon.h"
#include "cSprite.h"
#include "cExplosion.h"
#include "cXAudio.h"
#include "cD3DXFont.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemySpawner.h"
#include "Bullets.h"

RECT ScoreR;

using namespace std;

const int PLAYER_SPEED = 6; //constant varible to update the speed of all directions of the player.

bool keys[4]; //Holds true or false for each key so it can update the player position.

string screen = "Menu";


HINSTANCE hInst; // global handle to hold the application instance
HWND wndHandle; // global variable to hold the window handle

// Get a reference to the DirectX Manager
static cD3DManager* d3dMgr = cD3DManager::getInstance();

// Get a reference to the DirectX Sprite renderer Manager 
static cD3DXSpriteMgr* d3dxSRMgr = cD3DXSpriteMgr::getInstance();

RECT clientBounds;

TCHAR szTempOutput[30];

vector<Enemy*> enemies;
vector<Enemy*>::iterator iter;

vector<Bullets*> bullets;
vector<Bullets*>::iterator iteratorB;

EnemySpawner* spawner;

int enemyStart=0;

Player* player;

cD3DXFont* font; 
char scoreStr[100];
int score;

cXAudio* SFX;


/*
==================================================================
* LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam,
* LPARAM lParam)
* The window procedure
==================================================================
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	

	// Check any available messages from the queue
	switch (message)
	{

	case WM_LBUTTONUP: // Creates a bullet if left mouse button is pressed
		{

			bullets.push_back(new Bullets(new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\Bullet.png"), player->GetPosition()));

		}
	case WM_KEYDOWN: // Used to control the spaceship, when any of the W,A,S and D keys are pressed implement there set direction.
					 //Also includes Key presses for navigating the menus
		{
			if(wParam == 'W'){
				keys[0] = true;
				keys[1] = false;
			}

			if(wParam == 'S'){
				keys[1] = true;
				keys[0] = false;
			}

			if(wParam == 'A'){
				keys[2] = true;
				keys[3]=false;
			}

			if(wParam == 'D'){
				keys[3] = true;
				keys[2]=false;
			}

			if(screen == "Menu"){

				if(wParam == 'G')
					screen = "Game";
				SFX->playSound(L"Sounds\\BackMusic.wav",true);
			}

			if(screen == "End"){

				if(wParam == 'R'){
					screen = "Menu";
					score = 0;
					spawner->enemies.clear();
					bullets.clear();
					player = new Player(new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\Player.png"));
					spawner->Reset();
				}
			}
			


			return 0;
		}

	case WM_KEYUP: // Turns the key to false so the ship no longer continues in the same direction
		{
			if(wParam == 'W'){
				keys[0] = false;
			}

			if(wParam == 'S'){
				keys[1] = false;
			}

			if(wParam == 'A'){
				keys[2] = false;
			}

			if(wParam == 'D'){
				keys[3] = false;
			}

			return 0;

		}
		case WM_CLOSE:
			{
			// Exit the Game
				PostQuitMessage(0);
				 return 0;
			}

		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
	}
	// Always return the message to the default window
	// procedure for further processing
	return DefWindowProc(hWnd, message, wParam, lParam);
}

/*
==================================================================
* bool initWindow( HINSTANCE hInstance )
* initWindow registers the window class for the application, creates the window
==================================================================
*/
bool initWindow( HINSTANCE hInstance )
{
	WNDCLASSEX wcex;
	// Fill in the WNDCLASSEX structure. This describes how the window
	// will look to the system
	wcex.cbSize = sizeof(WNDCLASSEX); // the size of the structure
	wcex.style = CS_HREDRAW | CS_VREDRAW; // the class style
	wcex.lpfnWndProc = (WNDPROC)WndProc; // the window procedure callback
	wcex.cbClsExtra = 0; // extra bytes to allocate for this class
	wcex.cbWndExtra = 0; // extra bytes to allocate for this instance
	wcex.hInstance = hInstance; // handle to the application instance
	wcex.hIcon = LoadIcon(hInstance,MAKEINTRESOURCE(IDI_MyWindowIcon)); // icon to associate with the application
	wcex.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_GUNSIGHT));// the default cursor
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); // the background color
	wcex.lpszMenuName = NULL; // the resource name for the menu
	wcex.lpszClassName = "Balloons"; // the class namea being created
	wcex.hIconSm = LoadIcon(hInstance,"Balloon.ico"); // the handle to the small icon

	RegisterClassEx(&wcex);
	// Create the window
	wndHandle = CreateWindow("Balloons",			// the window class to use
							 "Balloon Burst",			// the title bar text
							WS_OVERLAPPEDWINDOW,	// the window style
							CW_USEDEFAULT, // the starting x coordinate
							CW_USEDEFAULT, // the starting y coordinate
							1600, // the pixel width of the window
							8001, // the pixel height of the window
							NULL, // the parent window; NULL for desktop
							NULL, // the menu for the application; NULL for none
							hInstance, // the handle to the application instance
							NULL); // no values passed to the window
	// Make sure that the window handle that is created is valid
	if (!wndHandle)
		return false;
	// Display the window on the screen
	ShowWindow(wndHandle, SW_SHOW);
	UpdateWindow(wndHandle);
	return true;
}

//This is my collide method where the bullets interect with the enemies and earse them from the game
void collide(){

	for(iteratorB = bullets.begin(); iteratorB != bullets.end(); ++iteratorB){ //loop through the bullet list

					(*iteratorB)->ShootBullet(); //Calling shoot bullet method on every bullet in list
					
					for(spawner->iter = spawner->enemies.begin(); spawner->iter != spawner->enemies.end(); ++spawner->iter){ //Goes through the spawners enemy list

						RECT rt;

						if(IntersectRect(&rt, &(*(spawner->iter))->ReturnBounds(), &(*iteratorB)->GetBounds())){ //Checks for a collison between bullets and enemies

							iteratorB = bullets.erase(iteratorB);// Earse bullet from bullet list
							spawner->iter = spawner->enemies.erase(spawner->iter);// Earse the enemy from the enemy list
							score++; // Increase score by 1 when a collision between bullet and enemy is made
							SFX->playSound(L"Sounds\\Boom.wav",false); //Plays sound effect when enemy is destroyed
							return;

						}
					}

					}
}
/*
==================================================================
// This is winmain, the main entry point for Windows applications
==================================================================
*/


int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow )
{
	// Initialize the window
	if ( !initWindow( hInstance ) )
		return false;
	// called after creating the window
	if ( !d3dMgr->initD3DManager(wndHandle) )
		return false;
	if ( !d3dxSRMgr->initD3DXSpriteMgr(d3dMgr->getTheD3DDevice()))
		return false;

	font = new cD3DXFont(d3dMgr->getTheD3DDevice(), hInst, "Ariel");
	score= 0;
	SetRect(&ScoreR,10,10,300,300);

	SFX = new cXAudio();
	

	// Grab the frequency of the high def timer
	__int64 freq = 0;				// measured in counts per second;
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	float sPC = 1.0f / (float)freq;			// number of seconds per count

	__int64 currentTime = 0;				// current time measured in counts per second;
	__int64 previousTime = 0;				// previous time measured in counts per second;

	float numFrames   = 0.0f;				// Used to hold the number of frames
	float timeElapsed = 0.0f;				// cumulative elapsed time

	GetClientRect(wndHandle,&clientBounds);

	float fpsRate = 1.0f/25.0f;

	LPDIRECT3DSURFACE9 menu;				// the Direct3D surface
	LPDIRECT3DSURFACE9 game;
	LPDIRECT3DSURFACE9 end;
	LPDIRECT3DSURFACE9 theBackbuffer = NULL;  // This will hold the back buffer
	
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );

	// Create the background surface
	menu = d3dMgr->getD3DSurfaceFromFile("Images\\Menu.JPG");
	game = d3dMgr->getD3DSurfaceFromFile("Images\\SpaceBackground.JPG");
	end = d3dMgr->getD3DSurfaceFromFile("Images\\End.JPG");

	QueryPerformanceCounter((LARGE_INTEGER*)&previousTime);

	player = new Player(new cD3DXTexture(d3dMgr->getTheD3DDevice(), "Images\\Player.png"));


	spawner=new EnemySpawner();
	

	while( msg.message!=WM_QUIT )
	{
		// Check the message queue
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		else
		{
			// Game code goes here
			QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
			float dt = (currentTime - previousTime)*sPC;

			// Accumulate how much time has passed.
			timeElapsed += dt;

			// Only update game objects if the screen is in Game 
			if(screen == "Game"){ 
			
				player->Tick();
				spawner->Spawner(d3dMgr);
				
				

			}

			
			if(timeElapsed >= fpsRate){

				if(keys[0])
					player->PositionUp(PLAYER_SPEED); //If true move player up

				if(keys[1])
					player->PositionDown(PLAYER_SPEED); //If true move player down            

				if(keys[3])
					player->PositionRight(PLAYER_SPEED); //If true move player right

				if(keys[2])
					player->PositionLeft(PLAYER_SPEED); //If true move player left
			
				// Updates the spawner
			if(screen=="Game"){
				spawner->Tick(player);

				collide(); // When a collision between the player and enemy happens go to game over screen

				if(spawner->End()){

					screen = "End";
				}
				
			sprintf_s(scoreStr,100,"Score %d",score); //Concatenates the two strings together and puts them into the score string array


			}

			/*
			==============================================================
			| Update the postion of the Enemies and check for collisions
			==============================================================
			*/
	
				d3dMgr->beginRender();
				theBackbuffer = d3dMgr->getTheBackBuffer();
				
				
				if(screen=="Menu"){
					d3dMgr->updateTheSurface(menu, theBackbuffer); //Draws the menu
				}
				if(screen=="Game"){
					d3dMgr->updateTheSurface(game, theBackbuffer); //Draws the main game
				}
				if(screen=="End"){
					d3dMgr->updateTheSurface(end, theBackbuffer); //Draws the game over screen
				}


			
				
				d3dMgr->releaseTheBackbuffer(theBackbuffer);
				  
				d3dxSRMgr->beginDraw();

				// When the game is actual draw everything
				if(screen=="Game"){

					player->Render(d3dxSRMgr);
					spawner->DrawEnemies(d3dxSRMgr);

					for(iteratorB = bullets.begin(); iteratorB != bullets.end(); ++iteratorB){

						(*iteratorB)->RenderBullet(d3dxSRMgr);

					}



				}

				d3dxSRMgr->endDraw();
				font->printText(scoreStr,ScoreR); //Printing the score string
				d3dMgr->endRender();
				timeElapsed = 0.0f;
			}
		}
			
			previousTime = currentTime;
		}

	d3dxSRMgr->cleanUp();
	d3dMgr->clean();

	return (int) msg.wParam;
}


