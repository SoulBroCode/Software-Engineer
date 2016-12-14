#include <iostream>
#include <thread>


#include <vector>
#include <queue>
#include "SDL.h"


class ThreadPool {
private:

	std::vector<SDL_Thread*> _threadPool;
	std::vector<std::function<void()>> _tasks;
	SDL_mutex* _taskLock;
	//SDL_sem* _lock;
	
public:
	ThreadPool(char numOfThread);
	int test;
	
	~ThreadPool() 
	{
		SDL_DestroyMutex(_taskLock);
		//SDL_DestroySemaphore(_lock);
	}
	


	void addJob(std::function<void()> job) {


		_tasks.push_back(job);


	}


};
static int worker(void* data)
{
	ThreadPool *threadPool = static_cast<ThreadPool*>(data);
	while (true)
	{
		SDL_Delay(400);
		std::cout << "Test : " << threadPool->test <<"\n";
	}

	return 0;
}
