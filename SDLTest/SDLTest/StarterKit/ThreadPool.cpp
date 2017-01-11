#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	mJobLock = SDL_CreateMutex();
}

ThreadPool::ThreadPool(char numOfThread, Map* map, AStar* AStar, Player* player)
{
	mMap = map;
	mAStar = AStar;
	mPlayer = player;
	//mPlayer = player;
	for (char i = 0; i < numOfThread; i++)
	{
		mThreadPool.push_back(SDL_CreateThread(worker, "test", this));
	}
	mJobLock = SDL_CreateMutex();

}

ThreadPool::~ThreadPool()
{
	SDL_DestroyMutex(mJobLock);
	//SDL_DestroySemaphore(_lock);
}

ThreadData* ThreadPool::getJob()
{
	if (!mJob.empty())
	{
		ThreadData* task = mJob[0];
		mJob.erase(mJob.begin());
		return task;
	}
	return nullptr;
}

void ThreadPool::addJob(ThreadData*  job)
{
	SDL_LockMutex(mJobLock);
	mJob.push_back(job);
	SDL_UnlockMutex(mJobLock);
}