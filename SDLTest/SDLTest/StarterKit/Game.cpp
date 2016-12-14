#include <Game.h>
#include <iostream>
#include <thread>



using namespace std;

SDL_sem* Game::lock = NULL;
int thread_A(void *data)
{
	Astar *algo = static_cast<Astar*>(data);
	while (true)
	{	
		SDL_SemWait(Game::lock);
		algo->test++;
		std::cout << "Thread 1 : " << algo->test  << "\n";
		SDL_Delay(200);
		SDL_SemPost(Game::lock);
		
	}
	return 0;
}

int thread_B(void *data)
{
	Astar *algo = static_cast<Astar*>(data);
	while (true)
	{
		SDL_SemWait(Game::lock);
		algo->test++;
		std::cout << "Thread 2 : " << algo->test << "\n";
		SDL_Delay(200);
		SDL_SemPost(Game::lock);
	}
	return 0;
}

int thread_C(void *data)
{
	Astar *algo = static_cast<Astar*>(data);
	while (true)
	{
		SDL_SemWait(Game::lock);
		algo->test++;
		std::cout << "Thread 3 : " << algo->test << "\n";
		SDL_Delay(200);
		SDL_SemPost(Game::lock);
	}
	return 0;
}
int thread_D(void *data)
{
	Astar *algo = static_cast<Astar*>(data);
	while (true)
	{
		SDL_SemWait(Game::lock);
		algo->test++;
		std::cout << "Thread 4 : " << algo->test << "\n";
		SDL_Delay(200);
		SDL_SemPost(Game::lock);
	}
	return 0;
}

int thread_E(void *data)
{
	Astar *algo = static_cast<Astar*>(data);
	while (true)
	{
		SDL_SemWait(Game::lock);
		algo->test++;
		std::cout << "Thread 5 : " << algo->test << "\n";
		SDL_Delay(200);
		SDL_SemPost(Game::lock);
	}
	return 0;
}

int thread_F(void *data)
{
	Astar *algo = static_cast<Astar*>(data);
	while (true)
	{
		SDL_SemWait(Game::lock);
		algo->test++;
		std::cout << "Thread 6 : " << algo->test << "\n";
		SDL_Delay(200);
		SDL_SemPost(Game::lock);
	}
	return 0;
}


Game::Game() : _loopRunning(false), _gameStage(1), _cameraOffsetX(0), _cameraOffsetY(0)
{
}

Game::~Game()
{
}



bool Game::Initialize(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		pool = new ThreadPool(1);
		lastTime = LTimer::gameTime();

		std::srand(std::time(0));
		DEBUG_MSG("SDL Init success");
		_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
		
	
		
		
		
		int mapWidth;
		InitializeLevel(mapWidth);
		InitializeAI(mapWidth);

		

		/////////////////////AI////////////////////////

		lock = SDL_CreateSemaphore(2);
		/*
		threadA = SDL_CreateThread(thread_A, "1",algo);
		threadB = SDL_CreateThread(thread_B, "2", algo);
		threadC = SDL_CreateThread(thread_C, "3", algo);
		threadD = SDL_CreateThread(thread_D, "4", algo);
		threadE = SDL_CreateThread(thread_E, "5", algo); 
		threadF = SDL_CreateThread(thread_F, "6", algo);*/
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
	_loopRunning = true;

	return true;
}
void Game::InitializeLevel(int &mapWidth)
{
	Camera *cam = Camera::getInstance();

	int spawnRegionOffset;
	int walls;
	int wallLenght;
	_gameStage = GAME_STAGE_1;
	switch (_gameStage)
	{
	case GAME_STAGE_1:
		mapWidth = 30;
		walls = 3;
		wallLenght = 25;
		cam->setSize(mapWidth, mapWidth);
		break;
	case GAME_STAGE_2:
		mapWidth = 100;
		walls = 6;
		wallLenght = 0;
		cam->setSize(mapWidth, mapWidth);
		break;
	default:
		mapWidth = 1000;
		walls = 18;
		wallLenght = 500;
		cam->setSize(mapWidth, mapWidth);
		break;
	}
	
	spawnRegionOffset = mapWidth / (walls * 2);
	float tileSize = 10;
	
	cam->setMaxPosX(mapWidth - 10);
	cam->setMaxPosX(mapWidth - 10);

	_baseMap = new Map(mapWidth, mapWidth, tileSize, tileSize, 1);
	_baseMap->generateWall(walls, spawnRegionOffset, wallLenght);
}
void Game::InitializeAI(int width)
{
	algo = new Astar(_baseMap);
	_baseMap->setGridVal(1, 1, GRID_END);
	_end = _baseMap->getEndGrid();
	//_baseMap->setGridVal(width - 1, width - 1, GRID_START);
	//Grid* start = _baseMap->getStartGrid();
	
	for (int i = 0; i < _maxAI; i++)
	{
		
		//int randomX = 5 + rand() % (width - 8);
		//int randomY = 5 + rand() % (width - 8);
		int randomX = width - 2;
		int randomY = width - 2;
		std::cout << "(X : " << randomX << ",Y : " << randomY << ")";
		AI* ai = new AI();
		ai->init(_baseMap);
		ai->setStartGrid(new Grid(randomX, randomY));

		algo->setHeuristicFunc(_heuFunc);
		algo->findPath(ai->getStartGrid(), _end);
		ai->setPath(algo->paths);
		_ai.push_back(ai);
		_baseMap->resetStatus();
	}

}

void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");
}

void Game::Update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update
	for (int i = 0; i < _maxAI; i++)
	{
		_ai[i]->update(deltaTime);
	}
	lastTime = currentTime;	//save the curent time for next frame
}

void Game::Render()
{
	SDL_RenderClear(_renderer);

	
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_baseMap->draw(_renderer);





	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	
	SDL_RenderPresent(_renderer);
}



void Game::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch(event.type)
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					_loopRunning = false;
					break;
				case SDLK_a:
				{
					DEBUG_MSG("A Key Pressed");
					Camera *cam = Camera::getInstance();
					unsigned short posX = cam->getPosX();
					if (posX > 0)
					{
						cam->setPosX(--posX);
					}
					break;
				}
				case SDLK_d:
				{
					DEBUG_MSG("D Key Pressed");
					Camera *cam = Camera::getInstance();
					unsigned short posX = cam->getPosX();
					if (posX < cam->getMaxPosX())
					{
						cam->setPosX(++posX);
					}
					break;
				}
				case SDLK_w:
				{
					DEBUG_MSG("W Key Pressed");
					Camera *cam = Camera::getInstance();
					unsigned short posY = cam->getPosY();
					if (posY > 0)
					{
						cam->setPosY(--posY);
					}
					break;
				}
				case SDLK_s:
				{
					DEBUG_MSG("S Key Pressed");
					Camera *cam = Camera::getInstance();
					unsigned short posY = cam->getPosY();
					if (posY < cam->getMaxPosX())
					{
						cam->setPosY(++posY);
					}
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
				
					for (std::vector<Grid*>::reverse_iterator it = algo->paths.rbegin(); it != algo->paths.rend(); ++it)
						std::cout << "x: " << (*it)->getX() << ", y: " << (*it)->getY() << "\n";
				
					break;
				}
				default:
					//SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
					break;
				}
	}
}



bool Game::IsRunning()
{
	return _loopRunning;
}

void Game::UnloadContent()
{
	DEBUG_MSG("Unloading Content");
	//delete(m_p_Texture);
	//m_p_Texture = NULL;
}

void Game::CleanUp()
{
	DEBUG_MSG("Cleaning Up");
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	SDL_Quit();
}

void Game::GenerateWall(int wallCount, int mapWidth) 
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