#include "A-star.h"

Astar::Astar(Map *map)
{
	_heuristicFunc = 1;		// Manhattan
	_refMap = map;
}

void Astar::setHeuristicFunc(int num)
{
	_heuristicFunc = num;
}

double Astar::heuristicFunction(Grid current, Grid target)
{
	double tmp = 0.0f;
	// Manhattan Distance
	if (_heuristicFunc == 1)
		tmp = abs(target.getY() - current.getY()) + 
			abs(target.getX() - current.getX());
	else tmp = sqrt((target.getY() - current.getY())*(target.getY() - current.getY()) +
			(target.getX() - current.getX())*(target.getX() - current.getX())); // Euclidean

	return tmp;
}

void Astar::rebuildPath(std::vector<Grid*> &paths, Grid *start, Grid *end, int &loopCount)
{

	if (end->getGridVal() != GRID_END && end->getGridVal() != GRID_START) 
	{
		loopCount++;
		end->setGridVal(GRID_PATH);
		Grid* path = new Grid();
		path->init(end->getX(), end->getY());
		paths.push_back(path);
		//lete path;
	
	}
	
	if (start != end && loopCount < 3000)
		rebuildPath(paths, start, end->getParent(), loopCount);
	else if (start == end)
		_refToLastGrid = nullptr;
	else
		_refToLastGrid = end->getParent();

}

struct compare  
{  
	bool operator()(Grid* l, Grid* r)  
	{  
		return (l->getF() > r->getF());  
	}  
};  
/*
bool Astar::findPath(Grid *start, Grid *end)
{
	
	
	Map copyMap = *_refMap;
	//memcpy(&copyMap, &_refMap, sizeof(_refMap));
	 

	std::priority_queue<Grid*, std::vector<Grid*>, compare > *open_list = new std::priority_queue<Grid*, std::vector<Grid*>, compare >();

	// std::vector<Grid*> *close_list = new std::vector<Grid*>();
	start = copyMap.getStartGrid();
	end = copyMap.getEndGrid();
	start->setStatus(GRID_STATUS_OPEN);

	start->setG(0.0f);
	double t = heuristicFunction(*start, *end);
	start->setH(t);

	Grid* current = start;
	open_list->push(current);

	while (current != end)
	{
		if (open_list->size() == 0)
		{
			return false;
		}
		current = open_list->top();
		open_list->pop();
		current->setStatus(GRID_STATUS_CLOSE);

		if (current == end)
		{
			//Grid *refToFromGrid = nullptr;
			Grid	 *_refToLastGrid;
			int loopCount = 0;
			rebuildPath(start, end, loopCount);
			if (_refToLastGrid != nullptr) 
			{
				loopCount = 0;
				rebuildPath(start, _refToLastGrid, loopCount);
				if (_refToLastGrid != nullptr) {
					loopCount = 0;
					rebuildPath(start, _refToLastGrid, loopCount);
				}
			}
				
				

			
			
			//"DONE! PATH FOUND! Path Length = ";

			return true;
		}

		for (int d = 0; d < 4; d++)
		{
			Grid* neighbor = copyMap.getNeighbor(current, d);
			if (neighbor != nullptr)
				if (neighbor->getStatus() != GRID_STATUS_CLOSE)
				{
					if (neighbor->getStatus() != GRID_STATUS_OPEN)
					{
						neighbor->setStatus(GRID_STATUS_OPEN);
						neighbor->setG(current->getG() + 1.0f);
 						double tmp = heuristicFunction(*neighbor, *end);
						neighbor->setH(tmp);
						neighbor->setParent(current);

						

						open_list->push(neighbor);
					}
					else {
						double tmp = current->getG() + 1.0f;
						if (tmp < neighbor->getG())
						{
							neighbor->setG(tmp);
							neighbor->setParent(current);
						

							std::make_heap(const_cast<Grid**>(&open_list->top()),
								const_cast<Grid**>(&open_list->top()) + open_list->size(),
								compare());
						}
					}
				}
		}
	}
	return true;
}*/

const std::vector<Grid*>& Astar::findPath( short AIPosX,short AIPosY, short PlayerPosX, short PlayerPosY)
{
	std::cout << "starting Astar";
	paths.clear();
	Map copyMap = *_refMap;

	copyMap.setGridVal(AIPosX, AIPosY, 17);
	copyMap.setGridVal(PlayerPosX, PlayerPosY, 16);



	std::priority_queue<Grid*, std::vector<Grid*>, compare > *open_list = new std::priority_queue<Grid*, std::vector<Grid*>, compare >();

	Grid *start = copyMap.getGrid(AIPosX, AIPosY);
	Grid *end = copyMap.getGrid(PlayerPosX, PlayerPosY);
	start->setStatus(GRID_STATUS_OPEN);

	start->setG(0.0f);
	double t = heuristicFunction(*start, *end);
	start->setH(t);

	Grid* current = start;
	open_list->push(current);

	while (current != end)
	{
		if (open_list->size() == 0)
		{
			return paths;
		}
		current = open_list->top();
		open_list->pop();
		current->setStatus(GRID_STATUS_CLOSE);

		if (current == end)
		{
			int loopCount = 0;
			rebuildPath(paths, start, end, loopCount);
			
			if (_refToLastGrid != nullptr)
			{
				loopCount = 0;
				rebuildPath(paths,start, _refToLastGrid, loopCount);
				if (_refToLastGrid != nullptr) {
					loopCount = 0;
					rebuildPath(paths,start, _refToLastGrid, loopCount);
				}
			}

			delete(open_list);
			open_list = nullptr;

			return paths;
		}

		for (int d = 0; d < 4; d++)
		{
			Grid* neighbor = copyMap.getNeighbor(current, d);
			if (neighbor != nullptr)
				if (neighbor->getStatus() != GRID_STATUS_CLOSE)
				{
					if (neighbor->getStatus() != GRID_STATUS_OPEN)
					{
						neighbor->setStatus(GRID_STATUS_OPEN);
						neighbor->setG(current->getG() + 1.0f);
						double tmp = heuristicFunction(*neighbor, *end);
						neighbor->setH(tmp);
						neighbor->setParent(current);



						open_list->push(neighbor);
					}
					else {
						double tmp = current->getG() + 1.0f;
						if (tmp < neighbor->getG())
						{
							neighbor->setG(tmp);
							neighbor->setParent(current);


							std::make_heap(const_cast<Grid**>(&open_list->top()),
								const_cast<Grid**>(&open_list->top()) + open_list->size(),
								compare());
						}
					}
				}
		}
	}
	return paths;
}


Astar::~Astar()
{
}