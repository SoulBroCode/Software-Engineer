#ifndef MYTHREADPOOL_H
#define MYTHREADPOOL_H
#include <iostream>
#include <thread>


#include <vector>
#include <queue>

#include "SDL.h"


class ThreadPool {
private:
	static ThreadPool* instance;

	SDL_mutex* _taskLock;

	//SDL_sem* _lock;
	
public:
	ThreadPool();
	ThreadPool(char numOfThread);
	~ThreadPool();
	static ThreadPool* getInstance();

	//ThreadData *data;
	std::vector<SDL_Thread*> _threadPool;
	std::vector<std::function<void(void*)>> _tasks;


	


	void addJob(std::function<void(void* data)> job) {
		SDL_LockMutex(_taskLock);
		_tasks.push_back(job);
		SDL_UnlockMutex(_taskLock);
	}

	std::function<void(void*)> getTask()
	{
		std::function<void(void*)> task = _tasks[0];
		_tasks.erase(_tasks.begin());
		return task;
	}

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
	
	ThreadPool *threadPool = ThreadPool::getInstance();
	//std::function<void(void*)> task = threadPool->getTask();

	
	//while (true)
	//{
	//	SDL_Delay(400);
	//task(threadPool->data);*/
	//}

	return 0;
}
#endif