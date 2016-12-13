#ifndef _MyThreadPool_H_
#define _MyThreadPool_H_


#include <iostream>
#include <algorithm>
#include <vector>
#include "Game.h"


class MyThreadPool {
private:
	int _maxThread;
	
public:
	std::vector<std::pair<SDL_Thread*, int>> pool;

	MyThreadPool() {}
	~MyThreadPool() 
	{
		//SDL_DestroySemaphore()
		//SDL_DestroyMutex();
	}

	
	void addJob()
	{
		for (int i = 0; i < _maxThread; i++)
		{
			//pool.push_back(std::make_pair(SDL_CreateThread(func, "1", NULL), 1));
		}
	}


};


static int func(void *data)
{
	
	while (true)
	{
		SDL_SemWait(Game::lock);
		
		std::cout << "Thread 1 : " <<  "\n";
		SDL_Delay(200);
		SDL_SemPost(Game::lock);

	}
	return 0;
}

#endif _MyThreadPool_H_