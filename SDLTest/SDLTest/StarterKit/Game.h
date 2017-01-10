#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <ctime>
#include <SDL_image.h>

#include "Camera.h"
#include "Debug.h"
#include "Grid.h"
#include "Map.h"
#include "A-star.h"
#include "LTimer.h"
#include "AI.h"
#include "Player.h"
#include "ThreadData.h"



class Game
{
public:
	Game();
	~Game();
	bool init(const char*, int, int, int, int, int);
	void loadContent();
	void unloadContent();
	void render();
	void update();
	void handleEvents();
	bool isRunning();
	void cleanUp();
	void generateWall(int wallCount, int mapWidth);

	void initLevel(int &mapWidth);
	void InitAI(int gameWidth);
	
	static SDL_sem *lock;
	SDL_mutex *mutexLock;
	Astar* _algo;
	std::vector<AI*> _ai;
	int _maxAI;
	Player * _player;
	Map newMap[7];
private:
	void InitLevelOne(int& wallCount, int& wallSize, float& tileSize);
	void InitLevelTwo();
	void InitLevelThree();

	enum Level
	{
		One,
		Two,
		Three
	};
	Level mLevel;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SDL_Surface* _surface;

	Map* _baseMap;

	Grid* _end;
	Grid* _start;

	int mScreenSize;

	int mEnemySpawnAreaMinX;
	int mEnemySpawnAreaMinY;
	int mEnemySpawnAreaMaxX;
	int mEnemySpawnAreaMaxY;

	int mPlayerSpawnAreaMinX;
	int mPlayerSpawnAreaMinY;
	int mPlayerSpawnAreaMaxX;
	int mPlayerSpawnAreaMaxY;

	bool mLoopRunning;
	
	unsigned int lastTime;//time of last update;

	
	
	
	

	
	int	_heuFunc;


	//The threads that will be used

	SDL_Thread *threadA = NULL;
	SDL_Thread *threadB = NULL;

	//The protective semaphore
	
	bool quit = false;

};

#endif

