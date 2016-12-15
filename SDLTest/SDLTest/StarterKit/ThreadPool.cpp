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

std::function<void(void*)> ThreadPool::getTask()
{
	std::function<void(void*)> task = _tasks[0];
	_tasks.erase(_tasks.begin());
	return task;
}

void ThreadPool::addJob(std::function<void(void* data)> job)
{
	SDL_LockMutex(_taskLock);
	_tasks.push_back(job);
	SDL_UnlockMutex(_taskLock);
}