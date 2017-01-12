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
	std::deque<ThreadData*> mJob;
	char mMaxThread;
	bool reset;
	//SDL_sem* _lock;
	
public:
	int mThreadFinish;
	bool mStop;
	SDL_mutex* mJobLock; //use spinning mutex to get job
	SDL_mutex* mEndLock; //use spinning mutex to destory thread via counter
	SDL_sem* mWaitLock; //semphore for adding jobs, only when there is a job that thread will run 
	Map* mMap;
	AStar* mAStar;
	Player* mPlayer;

	ThreadPool();
	ThreadPool(int numOfThread, Map* map, AStar* AStar, Player* player);
	~ThreadPool();
	


	

	ThreadData* ThreadPool::getJob();

	bool checkForFinish();

	void addJob(ThreadData*  job);


};


static int worker(void* data)
{
	ThreadPool *threadPool = static_cast<ThreadPool*>(data);
	Map map = *threadPool->mMap;
	AStar* aStar = threadPool->mAStar;
	Player* player = threadPool->mPlayer;
	
	
	while (!threadPool->mStop)
	{
		SDL_Delay(200);
		//SDL_SemWait(threadPool->mWaitLock);
		//spinning thread
		while (SDL_LockMutex(threadPool->mJobLock) != 0)
		{
		}
		ThreadData* t = threadPool->getJob(); 
		SDL_UnlockMutex(threadPool->mJobLock);
		if (t != nullptr)
		{
			std::cout << "Threading"<< std::endl;
			AI* ai = t->ai;
			ai->setPath(aStar->findPath(map, ai->getX(), ai->getY(), player->getX(), player->getY()));

		}	
	}
	
	while (SDL_LockMutex(threadPool->mEndLock) != 0)
	{
	}

	threadPool->mThreadFinish ++;
	SDL_UnlockMutex(threadPool->mEndLock);
	return 0;
}
#endif