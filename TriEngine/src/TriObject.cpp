#include "../include/TriObject.h"

Tri::Object::Object(AnimatedSprite &sprite)
: _sprite(sprite), position({0,0}), acceleration({0,0}){

}
Tri::Object::Object(AnimatedSprite &sprite, Vector2 position)
: _sprite(sprite), position(position), acceleration({0,0}) {

}

bool	Tri::Object::checkCollisionRec(Rectangle &rectangle) {
	return (this->_sprite.checkRecCollision(rectangle, this->position));
}

std::vector<Rectangle>	Tri::Object::getFrameHitboxes() {
	return (this->_sprite.getFrameSet().getFrameHitboxes());
}

void	Tri::Object::setCameraSpeed(float cameraSpeedFactor) {
	this->_sprite.setCameraSpeed(cameraSpeedFactor);
}

float	Tri::Object::getScale() const {
	return (this->_sprite.getScale());
}

Vector2	Tri::Object::getOrigin() const {
	return (this->_sprite.getOrigin());
}

Tri::AnimatedSprite	&Tri::Object::getSprite() {
	return (this->_sprite);
}

bool	Tri::Object::checkCollisionObj(Object &object) {
	std::vector<Rectangle>	recVec = object.getFrameHitboxes();
	Rectangle				hitbox;
	Vector2					position = object.position;
	float					scale = object.getScale();
	Vector2					origin = object.getOrigin();
	if (scale != 1.0)
	{
		for (auto &rectangle : recVec)
		{
			hitbox = {position.x + (rectangle.x * scale) - (origin.x * scale), position.y + (rectangle.x * scale) - (origin.y * scale), (rectangle.width * scale), (rectangle.height * scale)};
			if (this->checkCollisionRec(hitbox))
				return (true);
		}
	} else {
		for (auto &rectangle : recVec)
		{
			hitbox = {position.x + rectangle.x - origin.x, position.y + rectangle.x - origin.y, rectangle.width, rectangle.height};
			if (this->checkCollisionRec(hitbox))
				return (true);
		}
	}
	return (false);
}

void	Tri::Object::draw() const {
	this->_sprite.draw(this->position);
}