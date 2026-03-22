#include "../include/TriGroup.h"

Tri::Group::Group() : _hitbox({0,0,0,0}), cameraSpeed(1.0f) {}

Tri::Group::Group(Rectangle hitbox) : _hitbox(hitbox), cameraSpeed(1.0f) {}

// void	Tri::Group::addRectangle(Rectangle *rectangle, Color color) {
// 	this->_recVec.push_back({rectangle, color});
// }

void	Tri::Group::addObject(Tri::AnimatedSprite *sprite, int frameDelay, float scale, float rotation, Vector2 position, float maxSpeed, int type) {
	this->_objVec.emplace_back(sprite, frameDelay, scale, rotation, position, maxSpeed, type);
}

void	Tri::Group::addGroup(Tri::Group *group) {
	this->_groupVec.push_back(group);
}

bool	Tri::Group::checkGroupCollision(Rectangle &rectangle) {
	return (CheckCollisionRecs(rectangle, this->_hitbox));
}

bool	Tri::Group::checkGroupCollision(Tri::Object &object) {
	return (object.checkCollisionRec(this->_hitbox));
}

bool	Tri::Group::checkGroupCollision(Tri::Group &group) {
	return (CheckCollisionRecs(group.getHitboxRectangle(), this->_hitbox));
}

Rectangle	Tri::Group::getHitboxRectangle() const {
	return (this->_hitbox);
}

bool	Tri::Group::checkGroupCollisionAll(Tri::Group &group) {
	if (!this->checkGroupCollision(group))
		return (false);
	for	(const auto& groupGroup : this->_groupVec)
	{
		if (group.checkGroupCollisionAll(*groupGroup))
			return (true);
	}
	// for (const auto& groupRec : this->_recVec)
	// {
	// 	if (group.checkGroupCollisionAll(*(groupRec.first)))
	// 		return (true);
	// }
	for (auto& groupObj : this->_objVec)
	{
		if (group.checkGroupCollisionAll(groupObj))
			return (true);
	}
	return (false);
}

bool	Tri::Group::checkGroupCollisionAll(Rectangle &rectangle) {
	if (!this->checkGroupCollision(rectangle))
		return (false);
	for	(const auto& groupGroup : this->_groupVec)
	{
		if (groupGroup->checkGroupCollisionAll(rectangle))
			return (true);
	}
	// for (const auto& groupRec : this->_recVec)
	// {
	// 	if (CheckCollisionRecs(rectangle, *(groupRec.first)))
	// 		return (true);
	// }
	for (auto& groupObj : this->_objVec)
	{
		if (groupObj.checkCollisionRec(rectangle))
			return (true);
	}
	return (false);
}

bool	Tri::Group::checkGroupCollisionAll(Tri::Object &object) {
	if (!this->checkGroupCollision(object))
		return (false);
	for	(const auto& groupGroup : this->_groupVec)
	{
		if (groupGroup->checkGroupCollisionAll(object))
			return (true);
	}
	// for (const auto& groupRec : this->_recVec)
	// {
	// 	if (object.checkCollisionRec(*(groupRec.first)))
	// 		return (true);
	// }
	for (auto& groupObj : this->_objVec)
	{
		if (object.checkCollisionObj(groupObj))
			return (true);
	}
	return (false);
}

int			Tri::Group::supCollidedObj(Object &object) {
	if (!this->checkGroupCollision(object))
		return (false);
	int	type = 0;
	for	(const auto& groupGroup : this->_groupVec)
	{
		type = groupGroup->supCollidedObj(object);
		if (type)
			return (type);
	}
	for (auto it = this->_objVec.begin(); it != this->_objVec.end(); ++it)
	{
		if (object.checkCollisionObj(*it))
		{
			type = it->type;
			this->_objVec.erase(it);
			return (type);
		}
	}
	return (type);
}

void		Tri::Group::draw() {
	Rectangle	camera = Tri::camera().getSpeededCameraRec(this->cameraSpeed);
	if (!this->checkGroupCollision(camera))
		return ;
	for	(const auto& groupGroup : this->_groupVec)
	{
		if (groupGroup->checkGroupCollisionAll(camera))
			groupGroup->draw();
	}
	// for (const auto& groupRec : this->_recVec)
	// {
	// 	if (CheckCollisionRecs(camera, *(groupRec.first)))
	// 		Tri::drawRectangleCamera(*(groupRec.first), this->cameraSpeed, groupRec.second);
	// }
	for (auto& groupObj : this->_objVec)
	{
		if (groupObj.checkCollisionRec(camera))
			groupObj.draw();
	}
}

void	Tri::Group::setCameraSpeed(float cameraSpeedFactor) {
	this->cameraSpeed = cameraSpeedFactor;
	for	(const auto& groupGroup : this->_groupVec)
		groupGroup->setCameraSpeed(cameraSpeedFactor);
	for (auto& groupObj : this->_objVec)
		groupObj.setCameraSpeed(cameraSpeedFactor);
}

void	Tri::Group::findHitbox() {
	// Rectangle	hitbox;
	// if (!this->_recVec.empty())
	// 	hitbox = this->_recVec[0];
	// else
	// {
	// 	if (this->_objVec.empty())
	// 		return ;
	// 	hitbox = this->_objVec[0].getSprite().getFrameSet().getSpriteRectangle();
	// 	hitbox.x += this->_objVec[0].position.x - this->_objVec[0].getOrigin().x;
	// }
	// for (const auto& groupRec : this->_recVec)
	// {
	// 	if (object.checkCollisionRec(groupRec))
	// 		return (true);
	// }
	// for (const auto& groupObj : this->_objVec)
	// {
	// 	// if (object.checkCollisionObj(groupObj))
	// 	// 	return (true);
	// }
}
