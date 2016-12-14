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
	_posX(0),
	_posY(0),
	_maxPosX(0),
	_maxPosY(0),
	_sizeX(0),
	_sizeY(0)
{
}

Camera::~Camera()
{
	delete instance;
}

void Camera::setPosX(const unsigned short &posX)
{
	_posX = posX;
}
void Camera::setPosY(const unsigned short &posY)
{
	_posY = posY;
}
void Camera::setMaxPosX(const unsigned short &maxPosX)
{
	_maxPosX = maxPosX;
}
void Camera::setMaxPosY(const unsigned short &maxPosY)
{
	_maxPosY = maxPosY;
}
void Camera::setSize(const unsigned short &sizeX, const unsigned short &sizeY)
{
	_sizeX = sizeX;
	_sizeY = sizeY;
}


const unsigned short Camera::getPosX()
{
	return _posX;
}
const unsigned short Camera::getPosY()
{
	return _posY;
}
const unsigned short Camera::getMaxPosX()
{
	return _maxPosX;
}
const unsigned short Camera::getMaxPosY()
{
	return _maxPosY;
}
const unsigned short Camera::getSizeX()
{
	return _sizeX;
}
const unsigned short Camera::getSizeY()
{
	return _sizeY;
}