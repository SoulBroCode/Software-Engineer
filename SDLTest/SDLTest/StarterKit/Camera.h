#ifndef _MYCAMERA_H_
#define _MYCAMERA_H_
#include "SDL.h"

class Camera {
public:
	Camera();
	~Camera();
	static Camera* getInstance();

	void zoom(const short zoom);


	void setPosX(const unsigned short &posX);
	void setPosY(const unsigned short &posY);
	void setMaxPosX(const unsigned short &maxPosX);
	void setMaxPosY(const unsigned short &maxPosY);
	void setSize(const unsigned short &size);

	const unsigned short getPosX();
	const unsigned short getPosY();
	const unsigned short getMaxPosX();
	const unsigned short getMaxPosY();
	const unsigned short getSize();


private:
	static Camera* instance;
	unsigned short mPosX;
	unsigned short mPosY;
	unsigned short mMaxPosX;
	unsigned short mMaxPosY;
	unsigned short mSize;
	
};

#endif