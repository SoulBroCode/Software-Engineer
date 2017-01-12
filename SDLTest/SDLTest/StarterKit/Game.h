#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <ctime>
#include <SDL_image.h>
#include <iostream>

#include "ThreadPool.h"
#include "Camera.h"
#include "Debug.h"
#include "Grid.h"
#include "Map.h"
#include "AStar.h"
#include "LTimer.h"
#include "Player.h"
#include "AI.h"
#include "ThreadData.h"



class Game
{
public:
	Game();
	~Game();
	bool reset;
	bool init(const char*, int, int, int, int, int);
	void loadContent();
	void unloadContent();
	void render();
	void update();
	void handleEvents();
	bool isRunning();
	void cleanUp();

	void initLevel(int &mapWidth);
	void InitAI(int gameWidth);
	int counter;
private:
	void InitLevelOne();
	void InitLevelTwo();
	void InitLevelThree();

	enum Level
	{
		One,
		Two,
		Three
	};
	Level mLevel;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	SDL_Surface* mSurface;

	Map* mMap;
	AStar* mAStar;

	Player* mPlayer;
	std::vector<AI*> mAI;

	ThreadPool* mThreadPool;

	int mMaxAI;
	float mTileSize;
	int mScreenSize;

	int mEnemySpawnAreaX;
	int mEnemySpawnAreaY;


	int mPlayerSpawnAreaX;
	int mPlayerSpawnAreaY;


	bool mLoopRunning;
	
	unsigned int lastTime;//time of last update;
	
	int	mHeuFunc;
	
	bool quit = false;

};

#endif

