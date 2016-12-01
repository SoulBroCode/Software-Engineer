#ifndef _GRID_H_
#define _GRID_H_

#include <math.h>

class Grid {
private:
	int _status;
	int _value;
	int _x;
	int _y;

	Grid*	_parentGrid;

	double _G;
	double _H;

public:
	Grid();
	~Grid();
	
	void setStatus(int stat);
	void setGridVal(int val);
	void setH(double H);
	void setG(double G);
	void setGridCoord(int x, int y);
	void setParent(Grid* parent);

	int getStatus();
	int getGridVal();
	int getX();
	int getY();
	Grid* getParent();
	double getF();
	double getG();
};

#endif _GRID_H_