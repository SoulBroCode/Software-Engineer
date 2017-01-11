#include "Game.h"
#include <iostream>
#include <thread>



using namespace std;


int thread_A(void *data)
{
	Game *g = static_cast<Game*>(data);
	Map map = *g->mMap;

	while (true)
	{	
		//SDL_LockMutex(g->mutexLock);
		//if (g->player->getMoving())
		//{
			
			//g->ai->setPath(g->astar->findPath(g->ai->getX(), g->ai->getY(), g->player->getX(), g->player->getY()));
			
		//	g->player->setMoving(false);
		//}
		//SDL_UnlockMutex(g->mutexLock);
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
		lastTime = LTimer::gameTime();
		
		std::srand(std::time(0));
		DEBUG_MSG("SDL Init success");
		mScreenSize = width;
		mWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

	
	
		
		
		
		int mapSize;

		initLevel(mapSize);
		mPlayer = new Player(mMap, 2, 2);

		mAStar = new AStar();
		mAStar->setHeuristicFunc(0);
		mThreadPool = new ThreadPool(2, mMap, mAStar, mPlayer);

		InitAI(mapSize);



		//lock = SDL_CreateSemaphore(2);
		ThreadData* threadData = new ThreadData();

		threadData->ai = mAI[0];
		//threadA = SDL_CreateThread(thread_A, "1", this);

		if(mWindow != nullptr)
		{
			DEBUG_MSG("Window creation success");
			mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
			if(mRenderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
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
		mMaxAI = 5;
		wallCount = 3;
		wallSize = 20;

		cam->setSize(mapSize);
		tileSize = mScreenSize / (float)cam->getSize();
		break;
	case Level::Two:
		mapSize = 100;
		mMaxAI = 20;
		wallCount = 6;
		wallSize = 60;
		cam->setSize(mapSize);
		tileSize = mScreenSize / (float)cam->getSize();
		break;
	default:
		mapSize = 1000;
		wallCount = 18;
		wallSize = 0; //600
		mMaxAI = 1;
		cam->setSize(100);
		tileSize = mScreenSize / 100;
		break;
	}
	
	spawnRegionOffset = mapSize / (wallCount * 2);

	cam->setSize(mapSize);
	cam->setMaxPosX(mapSize);
	cam->setMaxPosY(mapSize);

	mMap = new Map(mapSize, mapSize, tileSize, tileSize, 1);
	mMap->generateWall(wallCount, spawnRegionOffset, wallSize);
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
	mMap->setGridVal(2, 2, GRID_END);
	
	

	
	for (int i = 0; i < 7; i++) {
		newMap[i] = *mMap;
	}
	

	for (int i = 0; i < 7; i++)
	{
		short posX = 5 + rand() % (width - 8);
		short posY = 5 + rand() % (width - 8);

		AI* ai = new AI(mMap, posX, posY);
		//ai->setPath(_algo->findPath(newMap[0], ai->getX(), ai->getY(), _player->getX(), _player->getY()));
		mAI.push_back(ai);
	}
	
	ThreadData* threadData = new ThreadData();
	threadData->ai = mAI[0];
	mThreadPool->addJob(threadData);
}

void Game::loadContent()
{
	DEBUG_MSG("Loading Content");
}

void Game::update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update

	if (mPlayer->getMoving()) {

		for (int i = 0; i < mAI.size(); i++)
		{

			Map mapTest = *mMap;
			mAI[i]->setPath(mAStar->findPath(mapTest, mAI[i]->getX(), mAI[i]->getY(), mPlayer->getX(), mPlayer->getY()));



		}
		mPlayer->setMoving(false);

	}

	bool finishLevel = true;
	for (int i = 0; i < mAI.size(); i++)
	{
		mAI[i]->update(deltaTime);
		
		if (mAI[i]->getReachPlayer() == 0)
		{
			finishLevel = false;
		}
	}

	if (finishLevel)
	{
		int i = 0;
	}
	
	
	mPlayer->update(deltaTime);


	lastTime = currentTime;	//save the curent time for next frame
}

void Game::render()
{
	SDL_RenderClear(mRenderer);

	
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);

	mMap->draw(mRenderer);





	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	
	SDL_RenderPresent(mRenderer);
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
					mMap->setGridWidth(mScreenSize / (float)cam->getSize());
					
					break;
				}
				case SDLK_e:
				{
					DEBUG_MSG("e Key Pressed");
					Camera *cam = Camera::getInstance();

					cam->zoom(1);
					mMap->setGridWidth(mScreenSize / (float)cam->getSize());
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
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
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