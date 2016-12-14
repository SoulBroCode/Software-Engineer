#ifndef _MYCAMERA_H_
#define _MYCAMERA_H_
#include "SDL.h"

class Camera {
public:
	Camera();
	~Camera();
	static Camera* getInstance();


	void setPosX(const unsigned short &posX);
	void setPosY(const unsigned short &posY);
	void setMaxPosX(const unsigned short &maxPosX);
	void setMaxPosY(const unsigned short &maxPosY);
	void setSize(const unsigned short &sizeX, const unsigned short &sizeY);

	const unsigned short getPosX();
	const unsigned short getPosY();
	const unsigned short getMaxPosX();
	const unsigned short getMaxPosY();
	const unsigned short getSizeX();
	const unsigned short getSizeY();
private:

	unsigned short _posX;
	unsigned short _posY;
	unsigned short _maxPosX;
	unsigned short _maxPosY;
	unsigned short _sizeX;
	unsigned short _sizeY;
	static Camera* instance;
};

#endif