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


typedef struct {
	Astar* param1;
	AI* param2;
} ThreadData;

class Game
{
public:
	Game();
	~Game();
	bool Initialize(const char*, int, int, int, int, int);
	void LoadContent();
	void UnloadContent();
	void Render();
	void Update();
	void HandleEvents();
	bool IsRunning();
	void CleanUp();
	void GenerateWall(int wallCount, int mapWidth);

	void InitializeLevel(int &mapWidth);
	void InitializeAI(int gameWidth);
	
	static SDL_sem *lock;
	SDL_mutex *mutexLock;
	Astar* _algo;
	std::vector<AI*> _ai;
	int _maxAI;
	Player * _player;

private:
	int screenSize;

	bool _loopRunning;
	unsigned int lastTime;//time of last update;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SDL_Surface* _surface;
	
	Map* _baseMap;

	Grid* _end;
	Grid* _start;
	
	
	

	
	int	_heuFunc;
	
	char _gameStage;
	unsigned short _cameraOffsetX;
	unsigned short _cameraOffsetY;

	//The threads that will be used

	SDL_Thread *threadA = NULL;
	SDL_Thread *threadB = NULL;

	//The protective semaphore
	
	bool quit = false;

};

#endif

