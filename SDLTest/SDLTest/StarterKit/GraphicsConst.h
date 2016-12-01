#ifndef _GRAPHICSCONST_H_
#define _GRAPHICSCONST_H_


#define GRAPHICS_INIT_FAILED	0x00
#define GRAPHICS_INIT_SUCCESS	0x01

#define FLAT_TOPPED				0x00
#define POINTY_TOPPED			0x01

#define GRID_SIZE				20
#define	UP						0x00
#define	RIGHT					0x02
#define LEFT					0x01
#define DOWN					0x03

#define COLOR_FIELD_GRID		al_map_rgb(153, 255, 255)
#define	COLOR_WALL_GRID			al_map_rgb(64, 64, 64)
#define	COLOR_CLOSED_GRID		al_map_rgb(153, 76, 0)
#define	COLOR_OPEN_GRID			al_map_rgb(0, 102, 0)
#define	COLOR_END_GRID			al_map_rgb(0, 139, 255)
#define	COLOR_START_GRID		al_map_rgb(255, 0, 139)
#define	COLOR_PATH				al_map_rgb(255, 255, 0)		

static char GRID_STATUS_FREE = 0;
static char GRID_STATUS_OPEN = 1;
static char GRID_STATUS_CLOSE = 255;


static char GRID_WALL = 0;
static char GRID_FIELD = 1;

static char GRID_END = 34;
static char GRID_START = 17;
static char GRID_PATH = 16;

static char GAME_STAGE_1 = 1;
static char GAME_STAGE_2 = 2;
static char GAME_STAGE_3 = 3;


//The dot dimensions
static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;

//The dimensions of the level
static const int LEVEL_WIDTH = 1280;
static const int LEVEL_HEIGHT = 960;


#endif _GRAPHICSCONST_H_