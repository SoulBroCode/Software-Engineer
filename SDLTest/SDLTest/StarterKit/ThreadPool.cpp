#include "ThreadPool.h"
ThreadPool* ThreadPool::instance = nullptr;

ThreadPool* ThreadPool::getInstance()
{
	if (instance == nullptr)
		instance = new ThreadPool();
	return instance;
}

ThreadPool::ThreadPool()
{
	
	for (char i = 0; i < 1; i++)
	{
		_threadPool.push_back(SDL_CreateThread(worker, "test",this));
	}
}
ThreadPool::~ThreadPool()
{
	SDL_DestroyMutex(_taskLock);
	//SDL_DestroySemaphore(_lock);
}