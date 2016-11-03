#pragma once
#include <SDL.h>
#include "Vector2D.h"

class Tile 
{
public:
	Tile();
	void Tile::Init(int const& _x, int const& _y, int const& _w, int const& _h);
	
	SDL_Rect const& getRect();
	Vector2f const& getOrigin();

private:
	SDL_Rect m_Rect;
	Vector2f m_Origin;
	
};
