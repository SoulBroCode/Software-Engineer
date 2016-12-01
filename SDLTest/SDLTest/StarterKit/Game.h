#ifndef GAME_H
#define GAME_H
#include "Debug.h"
#include <SDL.h>
#include "Grid.h"
#include "Map.h"
#include "A-star.h"
#include "SDL_image.h"

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
	void set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void fill_circle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
private:
	bool _loopRunning;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SDL_Surface* _surface;

	Map* _baseMap;
	Grid* _start;
	Grid* _end;
	int	_heuFunc;

	char _gameStage;
	unsigned short _cameraOffsetX;
	unsigned short _cameraOffsetY;
};

#endif

