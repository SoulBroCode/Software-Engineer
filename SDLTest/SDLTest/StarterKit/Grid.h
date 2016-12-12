#ifndef _GRID_H_
#define _GRID_H_

#include <math.h>

class Grid {
private:
	char _status;
	char _value;
	short _x;
	short _y;

	Grid* _parentGrid;

	float _G;
	float _H;

public:
	Grid();
	~Grid();
	
	void init(short x, short y);
	void setStatus(const char &stat);
	void setGridVal(const char &val);
	void setH(const float &H);
	void setG(const float &G);
	void setGridCoord(const int& x,const int &y);
	void setParent(Grid* parent);

	const char getStatus();
	const char getGridVal();
	const short getX();
	const short getY();
	Grid* getParent();
	const float getF();
	const float getG();
};

#endif _GRID_H_