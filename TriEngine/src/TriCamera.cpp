#include "../include/TriCamera.h"

Tri::Camera::Camera(Vector2 position) : _position(position) {
	this->refreshCamera();
}

Rectangle	Tri::Camera::getCameraRec() const {
	return (this->_cameraRec);
}

Rectangle	Tri::Camera::getSpeededCameraRec(float speedFactor) const {
	if (speedFactor == 1.0f)
		return (this->_cameraRec);
	return ((Rectangle){(this->_position.x * speedFactor) - this->_origin.x, (this->_position.y * speedFactor) - this->_origin.y, this->_cameraRec.width, this->_cameraRec.height});
}

Vector2	Tri::Camera::getPosition() const {
	return (this->_position);
}

void	Tri::Camera::setPosition(Vector2 position) {
	this->_position = position;
	this->_cameraRec.x = position.x - this->_origin.x;
	this->_cameraRec.y = position.y - this->_origin.y;
}

Vector2	Tri::Camera::convertPosition(Vector2 position, float factor) {
	if (factor == 1.0f)
		return ((Vector2){position.x - this->_cameraRec.x, position.y - this->_cameraRec.y});
	else
		return ((Vector2){(position.x - (this->_position.x * factor)) + this->_origin.x, (position.y - (this->_position.y * factor)) + this->_origin.y});
}

void	Tri::Camera::refreshCamera() {
	Vector2	screenSize = {static_cast<float>(GetScreenWidth()), static_cast<float>(GetScreenHeight())};
	this->_origin.x = screenSize.x / 2.0f;
	this->_origin.y = screenSize.y / 2.0f;
	this->_cameraRec = {this->_position.x - this->_origin.x , this->_position.y - this->_origin.y, screenSize.x, screenSize.y};
}

Tri::Camera	&Tri::camera() {
	static Tri::Camera camera({0, 0});
	return (camera);
}

Vector2	Tri::convertCamera(Vector2 position, float factor) {
	return (Tri::camera().convertPosition(position, factor));
}

void	Tri::drawRectangleCamera(Rectangle rectangle, float camSpeedFactor, Color color)
{
	Vector2	position = Tri::convertCamera({rectangle.x, rectangle.y}, camSpeedFactor);
	rectangle.x = position.x;
	rectangle.y = position.y;
	DrawRectangleRec(rectangle, color);
}
