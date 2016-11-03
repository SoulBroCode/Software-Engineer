#include "Tile.h"
Tile::Tile()
{
}

void Tile::Init( int const& _x,  int const& _y,  int const& _w, int const& _h)
{
	m_Rect = { _x,_y,_w,_h };
	m_Origin = { _x + _w*0.5f, _y + _h*0.5f };
}



SDL_Rect const& Tile::getRect()
{
	return m_Rect;
}
Vector2f const& Tile::getOrigin()
{
	return m_Origin;
}