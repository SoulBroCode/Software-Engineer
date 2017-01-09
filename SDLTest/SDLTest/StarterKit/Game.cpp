#include "Game.h"
#include <iostream>
#include <thread>



using namespace std;

SDL_sem* Game::lock = NULL;
int thread_A(void *data)
{
	Game *g = static_cast<Game*>(data);
	
	while (true)
	{	
		SDL_LockMutex(g->mutexLock);
		if (g->_player->getMoving())
		{
			for (int i = 0; i < g->_maxAI; i++)
			{

				g->_ai[i]->setPath(g->_algo->findPath(g->_ai[i]->getX(), g->_ai[i]->getY(), g->_player->getX(), g->_player->getY()));
				g->_ai[i]->ready();
			}
			g->_player->setMoving(false);
		}
		SDL_UnlockMutex(g->mutexLock);
	}
	

	
	return 0;

}



//Mutex
//	SDL_LockMutex(_taskLock);
//_tasks.push_back(job);
//SDL_UnlockMutex(_taskLock);
//
//SDL_SemWait(Game::lock);
//
//SDL_SemPost(Game::lock);


Game::Game() : mLevel(Level::One),mLoopRunning(false)
{
}

Game::~Game()
{
}



bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		ThreadPool* _threadpool = ThreadPool::getInstance();
		lastTime = LTimer::gameTime();
		
		std::srand(std::time(0));
		DEBUG_MSG("SDL Init success");
		mScreenSize = width;
		_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

	
	
		
		
		
		int mapSize;
		initLevel(mapSize);
		InitAI(mapSize);

		lock = SDL_CreateSemaphore(2);
		
		threadA = SDL_CreateThread(thread_A, "1", this);

		if(_window != nullptr)
		{
			DEBUG_MSG("Window creation success");
			_renderer = SDL_CreateRenderer(_window, -1, 0);
			if(_renderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
			}
			else
			{
				DEBUG_MSG("Renderer init fail");
				return false;
			}
		}
		else
		{
			DEBUG_MSG("Window init fail");
			return false;
		}
	}
	else
	{
		DEBUG_MSG("SDL init fail");
		return false;
	}
	mLoopRunning = true;

	return true;
}
void Game::initLevel(int &mapSize )
{
	Camera* cam = Camera::getInstance();

	int spawnRegionOffset;
	int wallCount;
	int wallSize;
	float tileSize;

	//mLevel = Level::One;
	switch (mLevel)
	{
	case Level::One:
		mapSize = 30;
		_maxAI = 5;
		wallCount = 3;
		wallSize = 20;

		cam->setSize(mapSize);
		tileSize = mScreenSize / (float)cam->getSize();
		break;
	case Level::Two:
		mapSize = 100;
		_maxAI = 20;
		wallCount = 6;
		wallSize = 60;
		cam->setSize(mapSize);
		tileSize = mScreenSize / (float)cam->getSize();
		break;
	default:
		mapSize = 1000;
		wallCount = 18;
		wallSize = 600;
		_maxAI = 1;
		cam->setSize(100);
		tileSize = mScreenSize / 100;
		break;
	}
	
	spawnRegionOffset = mapSize / (wallCount * 2);

	cam->setSize(mapSize);
	cam->setMaxPosX(mapSize);
	cam->setMaxPosY(mapSize);

	_baseMap = new Map(mapSize, mapSize, tileSize, tileSize, 1);
	_baseMap->generateWall(wallCount, spawnRegionOffset, wallSize);
}

#pragma region InitLevel
void Game::InitLevelOne(int& wallCount, int& wallSize, float& tileSize)
{
	
}

void Game::InitLevelTwo()
{

}

void Game::InitLevelThree()
{

}
#pragma endregion



void Game::InitAI(int width)
{
	_baseMap->setGridVal(2, 2, GRID_END);
	_player = new Player(_baseMap, 2, 2);
	_algo = new Astar(_baseMap);
	_algo->setHeuristicFunc(0);
	for (int i = 0; i < _maxAI; i++)
	{
		short posX = 5 + rand() % (width - 8);
		short posY = 5 + rand() % (width - 8);

		AI* ai = new AI(_baseMap, posX, posY);

		_ai.push_back(ai);
	}

}

void Game::loadContent()
{
	DEBUG_MSG("Loading Content");
}

void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update
	for (int i = 0; i < _maxAI; i++)
	{
		_ai[i]->update(deltaTime);
	}
	_player->update(deltaTime);
	lastTime = currentTime;	//save the curent time for next frame
}

void Game::render()
{
	SDL_RenderClear(_renderer);

	
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_baseMap->draw(_renderer);





	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	
	SDL_RenderPresent(_renderer);
}



void Game::handleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					mLoopRunning = false;
					break;
				case SDLK_a:
				{
					Camera *cam = Camera::getInstance();
					unsigned short posX = cam->getPosX();
					if (posX > 0)
					{
						cam->setPosX(posX -=10);
					}
					break;
				}
				case SDLK_d:
				{
					Camera *cam = Camera::getInstance();
					unsigned short posX = cam->getPosX();
					if (posX + cam->getSize() < cam->getMaxPosX())
					{
						cam->setPosX(posX += 10);
					}
					break;
				}
				case SDLK_w:
				{
					Camera *cam = Camera::getInstance();
					unsigned short posY = cam->getPosY();
					if (posY > 0)
					{
						cam->setPosY(posY -= 10);
					}
					break;
				}
				case SDLK_s:
				{
					Camera *cam = Camera::getInstance();
					unsigned short posY = cam->getPosY();
					if (posY + cam->getSize()< cam->getMaxPosX())
					{
						cam->setPosY(posY += 10);
					}
					break;
				}
				case SDLK_q:
				{
					DEBUG_MSG("S Key Pressed");
					Camera *cam = Camera::getInstance();
					
					cam->zoom(-1);
					_baseMap->setGridWidth(mScreenSize / (float)cam->getSize());
					
					break;
				}
				case SDLK_e:
				{
					DEBUG_MSG("e Key Pressed");
					Camera *cam = Camera::getInstance();

					cam->zoom(1);
					_baseMap->setGridWidth(mScreenSize / (float)cam->getSize());
					DEBUG_MSG(cam->getSize());
					break;
				}
				case SDLK_LEFT:
				{
					DEBUG_MSG("Left Key Pressed");

					break;
				}
				case SDLK_RIGHT:
				{
					DEBUG_MSG("Right Key Pressed");
					
					_end = _baseMap->getEndGrid();
					_baseMap->getGrid(_end->getX(), _end->getY())->setGridVal(GRID_FIELD);
					short posx = _end->getX() + 1;
					_baseMap->getGrid(posx, _end->getY())->setGridVal(GRID_END);
					_end = _baseMap->getEndGrid();
					_baseMap->resetMap();
					
					//algo->setHeuristicFunc(_heuFunc);
				
				
					break;
				}
				default:
					//SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
					break;
				}
	}
}



bool Game::isRunning()
{
	return mLoopRunning;
}

void Game::unloadContent()
{
	DEBUG_MSG("Unloading Content");
	//delete(m_p_Texture);
	//m_p_Texture = NULL;
}

void Game::cleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

void Game::generateWall(int wallCount, int mapWidth) 
{
	for (int i = 0; i < mapWidth; i++) 
	{
		for (int j = 0; j < mapWidth; j++)
		{

		}
	}
}




/*
void example()
{
	//Lock
	SDL_SemWait(lock);

	

	//Unlock
	SDL_SemPost(lock);
}*/