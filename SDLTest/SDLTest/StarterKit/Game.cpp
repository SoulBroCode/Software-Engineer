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
		
		lastTime = LTimer::gameTime();

		std::srand(std::time(0));
		DEBUG_MSG("SDL Init success");
		_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
		
	
		
		int mapWidth;
		int spawnRegionOffset;
		int walls;
		int wallLenght;
		_gameStage = GAME_STAGE_2;
		if (_gameStage == GAME_STAGE_1)
		{
			mapWidth = 30;
			walls = 3;
			wallLenght = 25;
			
		}
		else if (_gameStage == GAME_STAGE_2) {
			mapWidth = 100;
			walls = 6;
			wallLenght = 0;
		}
		else {
			mapWidth = 1000;
			walls = 18;
			wallLenght = 0;
		}
		spawnRegionOffset = mapWidth / (walls*2);
		float tileSize = width / mapWidth;
		//map
		_baseMap = new Map(mapWidth, mapWidth, tileSize, tileSize, 1);
		_baseMap->generateWall(walls, spawnRegionOffset, wallLenght);
		_baseMap->setGridVal(1, 1, GRID_END);
		algo = new Astar(_baseMap);
		//
		for (int i = 0; i < 3; i++)
		{

			AI* ai = new AI();
			ai->init(_baseMap);
			_ai.push_back(ai);
		}

		_end = _baseMap->getEndGrid();

		/////////////////////AI////////////////////////
		Grid* g1 = new Grid();
		g1->init(mapWidth - 8, mapWidth - 2);

	
		_ai[0]->setStartGrid(g1);

		algo->setHeuristicFunc(_heuFunc);
		algo->findPath(_ai[0]->getStartGrid(), _end);
		_ai[0]->setPath(algo->paths);
		_ai[0]->TICKCONST = 400;
		
		
		/////////////////////AI////////////////////////
		_baseMap->resetStatus();


		Grid* g2 = new Grid();
		g2->init(mapWidth - 2, mapWidth - 2);

		_ai[1]->setStartGrid(g2);
		//_heuFunc = 0;
		algo->setHeuristicFunc(_heuFunc);
		algo->findPath(_ai[1]->getStartGrid(), _end);
		_ai[1]->setPath(algo->paths);
		_ai[1]->TICKCONST = 300;
	
		/////////////////////AI////////////////////////
		Grid* g3 = new Grid();
		g3->init(mapWidth - 20, mapWidth - 2);

		_baseMap->setGridVal(mapWidth - 20, mapWidth - 2, GRID_START);
		_ai[2]->setStartGrid(g3);

		algo->setHeuristicFunc(_heuFunc);
		algo->findPath(_ai[2]->getStartGrid(), _end);
		_ai[2]->setPath(algo->paths);
		_ai[2]->TICKCONST = 200;

		algo->test = 0;
		
		lock = SDL_CreateSemaphore(2);
		threadA = SDL_CreateThread(thread_A, "1",algo);
		threadA = SDL_CreateThread(thread_B, "2", algo);
		threadA = SDL_CreateThread(thread_C, "3", algo);
		threadA = SDL_CreateThread(thread_D, "4", algo);
		threadA = SDL_CreateThread(thread_E, "5", algo); 
		threadA = SDL_CreateThread(thread_F, "6", algo);
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



void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");
}

void Game::Update()
{
	unsigned int currentTime = LTimer::gameTime();//millis since game started
	unsigned int deltaTime = currentTime - lastTime;//time since last update

	_ai[0]->update(deltaTime);
	_ai[1]->update(deltaTime);
	_ai[2]->update(deltaTime);
	lastTime = currentTime;	//save the curent time for next frame
}

void Game::Render()
{
	SDL_RenderClear(_renderer);

	
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_baseMap->draw(_renderer, _cameraOffsetX, _cameraOffsetY);





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
					DEBUG_MSG("A Key Pressed");
					if(_cameraOffsetX > 0)
						_cameraOffsetX--;
					DEBUG_MSG(_cameraOffsetX);
					break;
				case SDLK_d:
					DEBUG_MSG("D Key Pressed");
					if (_cameraOffsetX < 30000)
						_cameraOffsetX++;
					DEBUG_MSG(_cameraOffsetX);
					break;
				case SDLK_w:
					DEBUG_MSG("W Key Pressed");
					if (_cameraOffsetY > 0)
						_cameraOffsetY--;
					DEBUG_MSG(_cameraOffsetY);
					break;
				case SDLK_s:
					DEBUG_MSG("S Key Pressed");
					if (_cameraOffsetX < 30000)
						_cameraOffsetY++;
					DEBUG_MSG(_cameraOffsetY);
					break;
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