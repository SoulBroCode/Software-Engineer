#include <Game.h>
#include <iostream>
#include <thread>



using namespace std;

Game::Game() : m_running(false)
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
		m_p_Window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		
		m_Tile = new Tile[m_MaxTile];
		m_TileRect = new SDL_Rect[m_MaxTile];

		int tileLengthCount = sqrt(m_MaxTile);
		int tileSize = width / tileLengthCount;

		int currentTileIndex = 0;
		for (int i = 0; i < tileLengthCount; i++)
		{ 
			for (int j = 0; j < tileLengthCount; j++)
			{
				m_Tile[currentTileIndex].Init(j * tileSize, i*tileSize, tileSize, tileSize);
				m_TileRect[currentTileIndex] = m_Tile[currentTileIndex].getRect();
				currentTileIndex++;
			}
		}



		if(m_p_Window != 0)
		{
			DEBUG_MSG("Window creation success");
			m_p_Renderer = SDL_CreateRenderer(m_p_Window, -1, 0);
			if(m_p_Renderer != 0)
			{
				DEBUG_MSG("Renderer creation success");
				SDL_SetRenderDrawColor(m_p_Renderer, 255, 255, 255, 255);
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
	m_running = true;

	return true;
}



void Game::LoadContent()
{
	DEBUG_MSG("Loading Content");
	m_p_Surface = SDL_LoadBMP("assets/sprite.bmp");
	m_p_Texture = SDL_CreateTextureFromSurface(m_p_Renderer, m_p_Surface);
	SDL_FreeSurface(m_p_Surface);

	if(SDL_QueryTexture(m_p_Texture, NULL, NULL, &m_Source.w, &m_Destination.h)==0)
	{
		m_Destination.x = m_Source.x = 0;
		m_Destination.y = m_Source.y = 0;
		m_Destination.w = m_Source.w;
		m_Destination.h = m_Source.h;

		//DEBUG_MSG("Destination X:" + m_Destination.x);
		/*DEBUG_MSG("Destination Y:" + m_Destination.y);
		DEBUG_MSG("Destination W:" + m_Destination.w);
		DEBUG_MSG("Destination H:" + m_Destination.h);*/
	}
	else
	{
		DEBUG_MSG("Texture Query Failed");
		m_running = false;
	}
}

void Game::Render()
{

	SDL_RenderClear(m_p_Renderer);
	//DEBUG_MSG("Width Source" + m_Destination.w);
	//DEBUG_MSG("Width Destination" + m_Destination.w);

	if (m_p_Renderer != nullptr && m_p_Texture != nullptr)
	{
		SDL_SetRenderDrawColor(m_p_Renderer, 255, 0, 0, 255);

		
		///////////////rectangles////////

		SDL_RenderDrawRects(m_p_Renderer, m_TileRect, m_MaxTile);
		///////////circles///////
		for (int i = 0; i < m_MaxTile; i++)
		{
			fill_circle(m_p_Renderer, m_Tile[i].getOrigin().x, m_Tile[i].getOrigin().y, 7.5f, 0, 0, 222, 255);
			//draw_circle(m_p_Renderer, m_Tile[i].getOrigin().x, m_Tile[i].getOrigin().y, 15, 0, 0, 250, 255);
		}
		/////////////////////////////////



		SDL_SetRenderDrawColor(m_p_Renderer, 0, 0, 0, 255);
	}
		
		//SDL_RenderCopy(m_p_Renderer, m_p_Texture, NULL, NULL);
	SDL_RenderPresent(m_p_Renderer);
}

void Game::Update()
{
	//DEBUG_MSG("Updating....");
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
					m_running = false;
					break;
				case SDLK_UP:
					DEBUG_MSG("Up Key Pressed");
					if (SDL_RenderDrawPoint(m_p_Renderer, 500, 500) == 0)
					{

					}
					//SDL_SetRenderDrawColor(m_p_Renderer, 255, 0, 0, 255);
					break;
				case SDLK_DOWN:
					DEBUG_MSG("Down Key Pressed");
					//SDL_SetRenderDrawColor(m_p_Renderer, 0, 255, 0, 255);
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

void Game::set_pixel(SDL_Renderer *rend, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(rend, r, g, b, a);
	SDL_RenderDrawPoint(rend, x, y);
}
void Game::draw_circle(SDL_Renderer *surface, int n_cx, int n_cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	// if the first pixel in the screen is represented by (0,0) (which is in sdl)
	// remember that the beginning of the circle is not in the middle of the pixel
	// but to the left-top from it:

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
		/*
		// sleep for debug
		SDL_RenderPresent(gRenderer);
		std::this_thread::sleep_for(std::chrono::milliseconds{ 100 });
		*/
	}
}

void Game::fill_circle(SDL_Renderer *surface, int cx, int cy, int radius, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	// Note that there is more to altering the bitrate of this 
	// method than just changing this value.  See how pixels are
	// altered at the following web page for tips:
	//   http://www.libsdl.org/intro.en/usingvideo.html
	static const int BPP = 4;

	//double ra = (double)radius;

	for (double dy = 1; dy <= radius; dy += 1.0)
	{
		// This loop is unrolled a bit, only iterating through half of the
		// height of the circle.  The result is used to draw a scan line and
		// its mirror image below it.

		// The following formula has been simplified from our original.  We
		// are using half of the width of the circle because we are provided
		// with a center and we need left/right coordinates.

		double dx = floor(sqrt((2.0 * radius * dy) - (dy * dy)));
		int x = cx - dx;
		SDL_SetRenderDrawColor(surface, r, g, b, a);
		SDL_RenderDrawLine(surface, cx - dx, cy + dy - radius, cx + dx, cy + dy - radius);
		SDL_RenderDrawLine(surface, cx - dx, cy - dy + radius, cx + dx, cy - dy + radius);

		// Grab a pointer to the left-most pixel for each half of the circle
		/*Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
		Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
		for (; x <= cx + dx; x++)
		{
		*(Uint32 *)target_pixel_a = pixel;
		*(Uint32 *)target_pixel_b = pixel;
		target_pixel_a += BPP;
		target_pixel_b += BPP;
		}*/

		
	}
}


bool Game::IsRunning()
{
	return m_running;
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
	SDL_DestroyWindow(m_p_Window);
	SDL_DestroyRenderer(m_p_Renderer);
	SDL_Quit();
}
