
#ifndef _MYCAMERA_H_
#define _MYCAMERA_H_
#include "SDL.h"

class Camera
{
public:
	Camera(const unsigned c, unsigned short screenHeight);
private:
	unsigned short x;
	unsigned short y;
};


/*
void Game::set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(rend, r, g, b, a);
	SDL_RenderDrawPoint(rend, x, y);
}
void Game::draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{


	double error = (double)-radius;
	double x = (double)radius - 0.5;
	double y = (double)0.5;
	double cx = n_cx - 0.5;
	double cy = n_cy - 0.5;

	while (x >= y)
	{
		set_pixel(surface, (int)(cx + x), (int)(cy + y), r, g, b, a);
		set_pixel(surface, (int)(cx + y), (int)(cy + x), r, g, b, a);

		if (x != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy + y), r, g, b, a);
			set_pixel(surface, (int)(cx + y), (int)(cy - x), r, g, b, a);
		}

		if (y != 0)
		{
			set_pixel(surface, (int)(cx + x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy + x), r, g, b, a);
		}

		if (x != 0 && y != 0)
		{
			set_pixel(surface, (int)(cx - x), (int)(cy - y), r, g, b, a);
			set_pixel(surface, (int)(cx - y), (int)(cy - x), r, g, b, a);
		}

		error += y;
		++y;
		error += y;

		if (error >= 0)
		{
			--x;
			error -= x;
			error -= x;
		}

	}
}

void Game::fill_circle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

	static const int BPP = 4;


	for (double dy = 1; dy <= radius; dy += 1.0)
	{


		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(surface, r, g, b, a);
		SDL_RenderDrawLine(surface, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(surface, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);


	}
}
*/

#endif