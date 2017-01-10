
#ifndef _THREADDATA_H_
#define _THREADDATA_H_
#include "Player.h"
#include "A-star.h"
#include "AI.h"
class Player;
class Astar;
class AI;
struct ThreadData
{
	Player* player;
	AI* ai;
	Astar* astar;
}; 

#endif