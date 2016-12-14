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
	_size(0)
{
}

Camera::~Camera()
{
	delete instance;
}

void Camera::zoom(const short zoom)
{
	_size += zoom;
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
void Camera::setSize(const unsigned short &size)
{
	_size = size;
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
const unsigned short Camera::getSize()
{
	return _size;
}
