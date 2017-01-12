#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	mJobLock = SDL_CreateMutex();
}

ThreadPool::ThreadPool(int numOfThread, Map* map, AStar* AStar, Player* player)
{
	mMap = map;
	mAStar = AStar;
	mPlayer = player;
	mMaxThread = numOfThread;

	for (int i = 0; i < numOfThread; i++)
	{
		mThreadPool.push_back(SDL_CreateThread(worker, "thread" + i, this));
	}
	mJobLock = SDL_CreateMutex();
	mEndLock = SDL_CreateMutex();
	mWaitLock = SDL_CreateSemaphore(7);
	mThreadFinish = 0;
	mStop = false;
	reset = false;
}

ThreadPool::~ThreadPool()
{
	SDL_DestroyMutex(mJobLock);
	SDL_DestroySemaphore(mWaitLock);
	SDL_DestroyMutex(mEndLock);
	delete mMap;
	delete mAStar;
	delete mPlayer;
	
}
bool ThreadPool::checkForFinish()
{

	mJob.clear();//clear jobs
	if (mThreadFinish == mMaxThread)
	{
		
		for (int i = 0; i < mMaxThread; i++)
		{
			SDL_DetachThread(mThreadPool[i]); 
		}
		mThreadPool.clear();
		return true;
	}
	return false;
}

ThreadData* ThreadPool::getJob()
{

	if (!mJob.empty())
	{
		ThreadData* task = mJob.front();
		mJob.pop_front();
		return task;
	}
	return nullptr;
}

void ThreadPool::addJob(ThreadData*  job)
{
	mJob.push_back(job);
	//SDL_SemPost(mWaitLock);
}