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

	const unsigned short getPosX();
	const unsigned short getPosY();
	const unsigned short getMaxPosX();
	const unsigned short getMaxPosY();
private:

	unsigned short _posX;
	unsigned short _posY;
	unsigned short _maxPosX;
	unsigned short _maxPosY;

	static Camera* instance;
};

#endif