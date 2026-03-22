#include "../include/TriObject.h"

Tri::Object::Object(AnimatedSprite *sprite)
: _sprite(sprite), frameDelay(0), scale(1.0), rotation(0), position({0,0}), velocity({0,0}), maxSpeed(MAX_SPEED), accelerationSpeed(ACCELERATION_SPEED), friction(FRICTION), type(0) {

}

Tri::Object::Object(AnimatedSprite *sprite, int frameDelay, float scale, float rotation, Vector2 position, float maxSpeed, int type)
: _sprite(sprite), frameDelay(frameDelay), scale(scale), rotation(rotation), position(position), velocity({0,0}), maxSpeed(maxSpeed), accelerationSpeed(ACCELERATION_SPEED), friction(FRICTION), type(type) {

}
Tri::Object::Object(AnimatedSprite *sprite, Vector2 position)
: _sprite(sprite), frameDelay(0), scale(1.0), rotation(0), position(position), velocity({0,0}), maxSpeed(MAX_SPEED), accelerationSpeed(ACCELERATION_SPEED), friction(FRICTION), type(0) {

}

bool	Tri::Object::checkCollisionRec(Rectangle &rectangle) {
	return (this->_sprite->checkRecCollision(rectangle, this->position, this->scale, this->rotation));
}

bool	Tri::Object::checkCollisionCircle(Tri::Circle &circle) {
	return (this->_sprite->checkCircleCollision(circle, this->position, this->scale, this->rotation));
}

std::vector<Tri::Circle>	Tri::Object::getFrameHitboxes() {
	return (this->_sprite->getFrameSet().getFrameHitboxes());
}

void	Tri::Object::setCameraSpeed(float cameraSpeedFactor) {
	this->_sprite->setCameraSpeed(cameraSpeedFactor);
}

// float	Tri::Object::getScale() const {
// 	return (this->_sprite->getScale());
// }

Vector2	Tri::Object::getOrigin() const {
	return (this->_sprite->getOrigin());
}

Tri::AnimatedSprite	&Tri::Object::getSprite() {
	return (*(this->_sprite));
}

bool	Tri::Object::checkCollisionObj(Object &object) {
	std::vector<Tri::Circle>	circleVec = object.getFrameHitboxes();
	// Rectangle				hitbox;
	Vector2					position = object.position;
	float					rotation = object.rotation;
	float					scale = object.scale;
	// Vector2					origin = object.getOrigin();
	Tri::Circle				newCircle;
	for (auto &circle : circleVec)
	{
		newCircle = Tri::convertCircleToWorld(circle, position, scale, rotation);
		if (this->checkCollisionCircle(newCircle))
			return (true);
	}
	return (false);
}

void	Tri::Object::draw() const {
	this->_sprite->draw(this->position, this->scale, this->rotation, this->frameDelay);
}