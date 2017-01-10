
#include <iostream>
#include <thread>
#include <string>


#include <SDL.h>
#include <SDL_image.h>

#include "Game.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <string>
#include <queue>

using namespace std;
#undef main
int main(int argc, char** argv){

	

	Game* game = new Game();


	//Adjust screen positions as needed
	//DEBUG_MSG("Game Initialising");
	//game->Initialize("DGPP Skelatol",1200,0, 1200, 1200, SDL_WINDOW_INPUT_FOCUS);
	game->init("DGPP Skelatol", 200, 50, 900, 900, SDL_WINDOW_INPUT_FOCUS);
	//DEBUG_MSG("Loading Content");
	game->loadContent();


	//DEBUG_MSG("Game Loop Starting......");
	while(game->isRunning())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	//DEBUG_MSG("Calling Cleanup");
	game->cleanUp();
	game->unloadContent();
	
	return 0;
};
