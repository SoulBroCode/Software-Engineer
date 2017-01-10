#ifndef MYTHREADPOOL_H
#define MYTHREADPOOL_H
#include <iostream>
#include <thread>


#include <vector>
#include <queue>

#include "SDL.h"
#include "ThreadData.h"

class ThreadPool {
private:
	std::vector<SDL_Thread*> mThreadPool;
	std::vector<ThreadData*> mJob;
	SDL_mutex* mJobLock;

	//SDL_sem* _lock;
	
public:
	ThreadPool();
	ThreadPool(char numOfThread);
	~ThreadPool();

	//ThreadData *data;
	


	

	ThreadData* ThreadPool::getTask();
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
	
	//ThreadPool *threadPool = ThreadPool::getInstance();
	//std::function<ThreadData> task = threadPool->getTask();

	
	//while (true)
	//{
	//	SDL_Delay(400);
	//task(threadPool->data);*/
	//}

	return 0;
}
#endif