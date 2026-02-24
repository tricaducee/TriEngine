#include "../include/TriGravity.h"

Tri::Gravity::Gravity(Vector2 direction) {

}

Tri::Gravity::Gravity(Vector2 direction, float gravity) {

}

void	Tri::Gravity::applyGravity(Vector2 &position, Vector2 &acceleration) {
	this->_deltaTime = GetFrameTime();
	acceleration = {(this->_gravity * this->_deltaTime + acceleration.x) * this->_direction.x, (this->_gravity * this->_deltaTime + acceleration.y) * this->_direction.y};
	position.x += acceleration.x;
	position.y += acceleration.y;
}

void	Tri::Gravity::applyGravityCollision(Object &obj, Group &group) {

}

void	Tri::Gravity::applyGravityCollision(Rectangle &rectangle, Vector2 &acceleration, Group &group) {

}
