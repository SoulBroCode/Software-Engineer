#include "Camera.h"
#include "Camera.h"

Camera* Camera::instance = nullptr;

Camera* Camera::getInstance()
{
	if (instance == nullptr)
		instance = new Camera();
	return instance;
}

Camera::Camera() :
	mPosX(0),
	mPosY(0),
	mMaxPosX(0),
	mMaxPosY(0),
	mSize(0)
{
}

Camera::~Camera()
{
	delete instance;
}

void Camera::zoom(const short zoom)
{
	mSize += zoom;
}


void Camera::setPosX(const unsigned short &posX)
{
	mPosX = posX;
}
void Camera::setPosY(const unsigned short &posY)
{
	mPosY = posY;
}
void Camera::setMaxPosX(const unsigned short &maxPosX)
{
	mMaxPosX = maxPosX;
}
void Camera::setMaxPosY(const unsigned short &maxPosY)
{
	mMaxPosY = maxPosY;
}
void Camera::setSize(const unsigned short &size)
{
	mSize = size;
}


const unsigned short Camera::getPosX()
{
	return mPosX;
}
const unsigned short Camera::getPosY()
{
	return mPosY;
}
const unsigned short Camera::getMaxPosX()
{
	return mMaxPosX;
}
const unsigned short Camera::getMaxPosY()
{
	return mMaxPosY;
}
const unsigned short Camera::getSize()
{
	return mSize;
}
