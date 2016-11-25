#include <iostream>
#include <thread>
#include <string>


#include <SDL.h>
#include <SDL_image.h>

#include <Game.h>

#include <iostream>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <string>
#include <queue>

using namespace std;

int main(int argc, char** argv){

	DEBUG_MSG("Game Object Created");

	Game* game = new Game();


	//Adjust screen positions as needed
	DEBUG_MSG("Game Initialising");
	game->Initialize("DGPP Skelatol",100,50,900,900, SDL_WINDOW_INPUT_FOCUS);
	
	DEBUG_MSG("Loading Content");
	game->LoadContent();


	DEBUG_MSG("Game Loop Starting......");
	while(game->IsRunning())
	{
		game->HandleEvents();
		game->Update();
		game->Render();
	}

	DEBUG_MSG("Calling Cleanup");
	game->CleanUp();
	game->UnloadContent();
	
	return 0;
}
