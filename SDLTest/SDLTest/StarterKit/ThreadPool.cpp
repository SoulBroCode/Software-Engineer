#include "ThreadPool.h"

ThreadPool::ThreadPool()
{
	
	for (char i = 0; i < 1; i++)
	{
		mThreadPool.push_back(SDL_CreateThread(worker, "test",this));
	}
}
ThreadPool::~ThreadPool()
{
	SDL_DestroyMutex(mJobLock);
	//SDL_DestroySemaphore(_lock);
}

ThreadData* ThreadPool::getTask()
{
	ThreadData* task = mJob[0];
	mJob.erase(mJob.begin());
	return task;
}

void ThreadPool::addJob(ThreadData*  job)
{
	SDL_LockMutex(mJobLock);
	mJob.push_back(job);
	SDL_UnlockMutex(mJobLock);
}