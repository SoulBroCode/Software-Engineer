#include "ThreadPool.h"
ThreadPool::ThreadPool(char numOfThread)
{
	test = numOfThread;
	for (char i = 0; i < numOfThread; i++)
	{
		_threadPool.push_back(SDL_CreateThread(worker, "test",this));
	}
}
