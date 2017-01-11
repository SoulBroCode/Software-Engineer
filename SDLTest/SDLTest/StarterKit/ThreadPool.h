#ifndef MYTHREADPOOL_H
#define MYTHREADPOOL_H
#include <iostream>
#include <thread>


#include <vector>
#include <queue>

#include "SDL.h"
#include "ThreadData.h"
#include "Map.h"
#include "Player.h"
#include "AStar.h"
#include "AI.h"


class ThreadPool {
private:
	std::vector<SDL_Thread*> mThreadPool;
	std::vector<ThreadData*> mJob;
	SDL_mutex* mJobLock;
	
	//SDL_sem* _lock;
	
public:
	Map* mMap;
	AStar* mAStar;
	Player* mPlayer;
	//Player* mPlayer;
	ThreadPool();
	ThreadPool(char numOfThread, Map* map, AStar* AStar, Player* player);
	~ThreadPool();
	


	

	ThreadData* ThreadPool::getJob();

	void addJob(ThreadData*  job);


	static void action(void *data)
	{
		//ThreadData *tdata = static_cast<ThreadData*>(data);

		//Astar* a = tdata->param1;
		//AI* ai = tdata->param2;
		//ai->setPath(a->findPath(ai->getX(), ai->getY(), 1, 1));
		//ai->ready();
		std::cout << "hello at : " << " don";
	}

};


static int worker(void* data)
{
	ThreadPool *threadPool = static_cast<ThreadPool*>(data);
	Map map = *threadPool->mMap;
	AStar* aStar = threadPool->mAStar;
	Player* player = threadPool->mPlayer;
	(*player).print();

	
	while (true)
	{
		std::cout << "threading!!!!!" << std::endl;

		ThreadData* t = threadPool->getJob();
		if (t != nullptr)
		{
			AI* ai = t->ai;
			(*ai).print();
			//mPlayer = new Player(mMap, 2, 2);
			//ai->setPath(aStar->findPath(map, ai->getX(), ai->getY(), player->getX(), player->getY()));
			int i = 0;
		}
		//mAStar->findPath(mapTest, mAI[i]->getX(), mAI[i]->getY(), mPlayer->getX(), mPlayer->getY())
		//aStar->findPath(map, t->ai->getX(), t->ai->getY(), player->getX(), player->getY())
		//t->ai->setPath();
		SDL_Delay(20000);

		
	}

	return 0;
}
#endif