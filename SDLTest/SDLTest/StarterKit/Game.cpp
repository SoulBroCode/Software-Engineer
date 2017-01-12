#include "Game.h"

using namespace std;

Game::Game() : mLevel(Level::One),mLoopRunning(false)
{
	counter = 0;
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
		mPlayer = new Player(mMap, mPlayerSpawnAreaX, mPlayerSpawnAreaY);

		mAStar = new AStar();
		mAStar->setHeuristicFunc(0);
		

		if(mWindow != nullptr)
		{
			DEBUG_MSG("Window creation success");
			mRenderer = SDL_CreateRenderer(mWindow, -1, 0);
			if(mRenderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
				mThreadPool = new ThreadPool(7, mMap, mAStar, mPlayer);

				InitAI(mapSize);
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
	
	switch (mLevel)
	{
	case Level::One:
		InitLevelOne();
		mapSize = 30;
		mMaxAI = 5;
		wallCount = 3;                  
		wallSize = 20;

		cam->setSize(mapSize);
		mTileSize = mScreenSize / (float)cam->getSize();
		break;
	case Level::Two:
		InitLevelTwo();
		mapSize = 100;
		mMaxAI = 50;
		wallCount = 6;
		wallSize = 60;
		cam->setSize(mapSize);
		mTileSize = mScreenSize / (float)cam->getSize();
		break;
	default:
		InitLevelThree();
		mapSize = 1000;
		wallCount = 18;
		wallSize =  550; 
		mMaxAI = 500;
		cam->setSize(150);
		mTileSize = mScreenSize / 150;
		break;
	}
	
	spawnRegionOffset = mapSize / (wallCount * 2);

	
	cam->setMaxPosX(mapSize);
	cam->setMaxPosY(mapSize);
	mMap = nullptr;
	delete mMap;
	mMap = new Map(mapSize, mapSize, mTileSize, mTileSize, 1);
	mMap->generateWall(wallCount, spawnRegionOffset, wallSize);
}

#pragma region InitLevel
void Game::InitLevelOne()
{
	mEnemySpawnAreaX = 26; 
	mEnemySpawnAreaY = 12;

	mPlayerSpawnAreaX = 3;
	mPlayerSpawnAreaY = 15;
}

void Game::InitLevelTwo()
{
	mEnemySpawnAreaX = 96; 
	mEnemySpawnAreaY = 30;

	mPlayerSpawnAreaX = 3;
	mPlayerSpawnAreaY = 15;
}

void Game::InitLevelThree()
{
	mEnemySpawnAreaX = 980;
	mEnemySpawnAreaY = 300;

	mPlayerSpawnAreaX = 3;
	mPlayerSpawnAreaY = 15;
}
#pragma endregion



void Game::InitAI(int width)
{
	mMap->setGridVal(mPlayerSpawnAreaX, mPlayerSpawnAreaY, GRID_END);

	mAI.clear();
	
	short counter = 0;
	for (int i = 0; i < mMaxAI; i++)
	{
		counter++;
		short posX = mEnemySpawnAreaX + (rand() % 3) - 1;
		short posY = mEnemySpawnAreaY + counter;

		AI* ai = new AI(mMap, posX, posY);
		mAI.push_back(ai);
		ThreadData* threadData = new ThreadData();
		threadData->ai = mAI[i];
		mThreadPool->addJob(threadData);//first jobs added to pool
	
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


	mPlayer->update(deltaTime);
	bool finishLevel = true;
	for (int i = 0; i < mAI.size(); i++)
	{
		mAI[i]->update(deltaTime);
		
		if (mAI[i]->getReachPlayer() == 0) //if ai hasnt reach player
		{
			finishLevel = false;
			if (mAI[i]->getReachHalfWay())
			{
				ThreadData* threadData = new ThreadData();
				threadData->ai = mAI[i];
				mThreadPool->addJob(threadData);
				mAI[i]->setReachHalfWay(false);
			}
		}

	}
 
	if (finishLevel)
	{
		mThreadPool->mStop = true;
		if (mThreadPool->checkForFinish())
		{
			switch (mLevel)
			{
			case Level::One:
				mLevel = Level::Two;
				break;
			case Level::Two:
				mLevel = Level::Three;
				break;
			default:
				mLevel = Level::One;
				break;				
			}
			
			int size;
			initLevel(size);
			mPlayer = new Player(mMap, mPlayerSpawnAreaX, mPlayerSpawnAreaY);
			mThreadPool = new ThreadPool(7, mMap, mAStar, mPlayer);
			InitAI(size);
		}
		
	}
	
	
	


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
					break;
				}
				case SDLK_e:
				{

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
