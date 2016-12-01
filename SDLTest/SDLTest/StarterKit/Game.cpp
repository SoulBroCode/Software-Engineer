#include <Game.h>
#include <iostream>
#include <thread>



using namespace std;

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

		DEBUG_MSG("SDL Init success");
		_window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		
	
		float tileSize = 30;
		float mapWidth;
		_gameStage = GAME_STAGE_3;
		if (_gameStage == GAME_STAGE_1)
		{
			mapWidth = 30;
		}
		else if (_gameStage == GAME_STAGE_2) {
			mapWidth = 100;
		}
		else {
			mapWidth = 1000;
		}
		

		_baseMap = new Map(mapWidth, mapWidth, tileSize, tileSize, 1);
		_baseMap->getGrid(mapWidth - 1, mapWidth - 1)->setGridVal(GRID_START);
		_baseMap->getGrid(10, 0)->setGridVal(GRID_END);
		_baseMap->getGrid(10, 1)->setGridVal(GRID_WALL);
		_baseMap->getGrid(11, 1)->setGridVal(GRID_WALL);
		_baseMap->getGrid(11, 0)->setGridVal(GRID_WALL);
		_baseMap->getGrid(9, 1)->setGridVal(GRID_WALL);
		_start = _baseMap->getStartGrid();
		_end = _baseMap->getEndGrid();
		//Astar *algo = new Astar(_baseMap);
		//algo->setHeuristicFunc(_heuFunc);
		//algo->findPath(_start, _end);

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

void Game::Render()
{
	SDL_RenderClear(_renderer);

	
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);

	_baseMap->draw(_renderer, _cameraOffsetX, _cameraOffsetY);





	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	
	SDL_RenderPresent(_renderer);
}

void Game::Update()
{

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
					DEBUG_MSG("Left Key Pressed");
					//SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 255, 255);
					break;
				case SDLK_RIGHT:
					DEBUG_MSG("Right Key Pressed");
					//SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
					break;
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



