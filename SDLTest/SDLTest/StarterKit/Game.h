#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include "Grid.h"
#include "Map.h"
#include "A-star.h"
#include "SDL_image.h"
#include "LTimer.h"
#include "AI.h"
#include <ctime>
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
private:
	bool _loopRunning;
	unsigned int lastTime;//time of last update;

	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SDL_Surface* _surface;

	Map* _baseMap;

	Grid* _end;
	std::vector<AI*> _ai;



	int	_heuFunc;
	Astar *algo;
	char _gameStage;
	unsigned short _cameraOffsetX;
	unsigned short _cameraOffsetY;

	//The threads that will be used
	SDL_Thread *threadA = NULL;
	SDL_Thread *threadB = NULL;

	//The protective semaphore
	SDL_sem *lock = NULL;
};

#endif

