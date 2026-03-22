#include "../include/TriSprite.h"
#include "../include/TriCamera.h"
#include <cmath>
// #include <iostream>

Tri::FrameSet::FrameSet(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame)
: _spriteSheet(spriteSheet), _nFrame(nFrame), _origin({0, 0}), _frameIndex(0), _initStartIndex(0), _inCamera(true), _cameraSpeed(1.0f), _spriteRectangle(spriteRectangle) {
}

Tri::FrameSet::FrameSet(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin)
: _spriteSheet(spriteSheet), _nFrame(nFrame), _origin(origin), _frameIndex(0), _initStartIndex(0), _inCamera(true), _cameraSpeed(1.0f), _spriteRectangle(spriteRectangle) {
}


// Tri::FrameSet::~FrameSet() {

// }

void	Tri::FrameSet::setOrigin(Vector2 origin) {
	this->_origin = origin;
}

void	Tri::FrameSet::setOriginToCenter() {
	this->_origin.x = this->_spriteRectangle.width / 2.0;
	this->_origin.y = this->_spriteRectangle.height / 2.0;
}

void	Tri::FrameSet::setFrameIndex(unsigned int index) {
	this->_frameIndex = index % this->_nFrame;
}

void	Tri::FrameSet::setCameraSpeed(float speed) {
	this->_cameraSpeed = speed;
}
void	Tri::FrameSet::setInCamera(bool inCamera) {
	this->_inCamera = inCamera;
}

void	Tri::FrameSet::resetFrameIndex() {
	this->_frameIndex = this->_initStartIndex;
}

void	Tri::FrameSet::setInitStartIndex(unsigned int start){
	this->_initStartIndex = start % this->_nFrame;
	this->_frameIndex = this->_initStartIndex;
}

unsigned int	Tri::FrameSet::getFrameIndex() const {
	return (this->_frameIndex);
}


unsigned int	Tri::FrameSet::getNFrame() const {
	return this->_nFrame;
}

Vector2	Tri::FrameSet::getOrigin() const {
	return this->_origin;
}

float	Tri::FrameSet::getCameraSpeed() const {
	return (this->_cameraSpeed);
}

Rectangle		Tri::FrameSet::getSpriteRectangle() const {
	return (this->_spriteRectangle);
}

void	Tri::FrameSet::draw(Vector2 position) const {
	position = Tri::convertCamera(position, this->_cameraSpeed);
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};
	Rectangle	dest = {.x=position.x, .y=position.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x, this->_origin.y}, 0, WHITE);
}

void	Tri::FrameSet::draw(Vector2 position, float scale) const {
	position = Tri::convertCamera(position, this->_cameraSpeed);
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};
	Rectangle	dest = {.x=position.x, .y=position.y, .width=this->_spriteRectangle.width * scale, .height=this->_spriteRectangle.height * scale};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * scale, this->_origin.y * scale}, 0, WHITE);
}

void	Tri::FrameSet::drawDeformed(Rectangle dest) const {
	Vector2	position = Tri::convertCamera({dest.x, dest.y}, this->_cameraSpeed);
	dest.x = position.x;
	dest.y = position.y;
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * (dest.width / source.width), this->_origin.y * (dest.height / source.height)}, 0, WHITE);
}

void	Tri::FrameSet::draw(Vector2 position, float scale, float rotation) const {
	position = Tri::convertCamera(position, this->_cameraSpeed);
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};
	Rectangle	dest = {.x=position.x, .y= position.y, .width=this->_spriteRectangle.width * scale, .height=this->_spriteRectangle.height * scale};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * scale, this->_origin.y * scale}, rotation, WHITE);
}

void	Tri::FrameSet::drawDeformed(Rectangle dest, float rotation) const {
	Vector2	position = Tri::convertCamera({dest.x, dest.y}, this->_cameraSpeed);
	dest.x = position.x;
	dest.y = position.y;
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * (dest.width / source.width), this->_origin.y * (dest.height / source.height)}, rotation, WHITE);
}

void	Tri::FrameSet::draw(Vector2 position, float scale, float rotation, unsigned int indexDelay) const {
	position = Tri::convertCamera(position, this->_cameraSpeed);
	Rectangle	source = {.x=this->_spriteRectangle.x + ((indexDelay + this->_frameIndex) % this->_nFrame * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};
	Rectangle	dest = {.x=position.x, .y= position.y, .width=this->_spriteRectangle.width * scale, .height=this->_spriteRectangle.height * scale};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * scale, this->_origin.y * scale}, rotation, WHITE);
}

void	Tri::FrameSet::drawDeformed(Rectangle dest, float rotation, unsigned int index) const {
	Vector2	position = Tri::convertCamera({dest.x, dest.y}, this->_cameraSpeed);
	dest.x = position.x;
	dest.y = position.y;
	Rectangle	source = {.x=this->_spriteRectangle.x + (index % this->_nFrame * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * (dest.width / source.width), this->_origin.y * (dest.height / source.height)}, rotation, WHITE);
}

void	Tri::FrameSet::addFrameIndex() {
	this->_frameIndex = (this->_frameIndex + 1) % this->_nFrame;
}
void	Tri::FrameSet::addFrameIndex(unsigned int value) {
	this->_frameIndex = (this->_frameIndex + value) % this->_nFrame;
}
void	Tri::FrameSet::susFrameIndex() {
	this->_frameIndex = this->_frameIndex > 0 ? this->_frameIndex - 1 : this->_nFrame - 1;
}
void	Tri::FrameSet::susFrameIndex(unsigned int value) {
	this->_frameIndex = (value % this->_nFrame) > this->_frameIndex ? this->_nFrame - (value % this->_nFrame) - this->_frameIndex : this->_frameIndex - (value % this->_nFrame);
}

void	Tri::FrameSet::operator++() {
	this->addFrameIndex();
}

void	Tri::FrameSet::operator--() {
	this->susFrameIndex();
}

void	Tri::FrameSet::operator++(int) {
	this->addFrameIndex();
}

void	Tri::FrameSet::operator--(int) {
	this->susFrameIndex();
}

//-----------------------FrameSetHitbox----------------------------//

Tri::FrameSetHitbox::FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame)
: FrameSet(spriteSheet, spriteRectangle, nFrame), _hitboxesVec(nFrame) {}

Tri::FrameSetHitbox::FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin)
: FrameSet(spriteSheet, spriteRectangle, nFrame, origin), _hitboxesVec(nFrame) {}

Tri::FrameSetHitbox::FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, std::vector<std::vector<Tri::Circle>> hitboxesVec)
: FrameSet(spriteSheet, spriteRectangle, nFrame), _hitboxesVec(hitboxesVec) {
	if (this->_hitboxesVec.size() < nFrame)
		this->_hitboxesVec.resize(nFrame);
}

Tri::FrameSetHitbox::FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin, std::vector<std::vector<Tri::Circle>> hitboxesVec)
: FrameSet(spriteSheet, spriteRectangle, nFrame, origin), _hitboxesVec(hitboxesVec) {
	if (this->_hitboxesVec.size() < nFrame)
		this->_hitboxesVec.resize(nFrame);

}

std::vector<Tri::Circle>	Tri::FrameSetHitbox::getFrameHitboxes() const {
	return (this->_hitboxesVec[this->getFrameIndex()]);
}

std::vector<Tri::Circle>	Tri::FrameSetHitbox::getFrameHitboxes(unsigned int index) const {
	if (index < this->getFrameIndex())
		return (this->_hitboxesVec[index]);
	return (std::vector<Tri::Circle>());
}

void	Tri::FrameSetHitbox::addHitboxToFrame(unsigned int index, Tri::Circle hitBox) {
	if (index < this->getFrameIndex())
		this->_hitboxesVec[index].push_back(hitBox);
}

bool	Tri::FrameSetHitbox::checkRecCollision(Rectangle rec, Vector2 framePosition, float scale, float rotation) {
	// Vector2	origin = this->getOrigin();
	Tri::Circle	circle;
	// if (!CheckCollisionRecs(rec, {.x=framePosition.x - origin.x, .y=framePosition.y - origin.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height}))
	// 	return (false);
	for (const auto& hitbox : this->_hitboxesVec[this->getFrameIndex()]) {
		circle = Tri::convertCircleToWorld(hitbox, framePosition, scale, rotation);
		if (CheckCollisionCircleRec({circle.x, circle.y}, circle.radius, rec))
			return (true);
	}
	return (false);
}

bool	Tri::FrameSetHitbox::checkCircleCollision(Tri::Circle circle, Vector2 framePosition, float scale, float rotation) {
	// Vector2	origin = this->getOrigin();
	Tri::Circle	circleWorld;
	// if (!CheckCollisionCircleRec({circle.x, circle.y}, circle.radius, {.x=framePosition.x - origin.x, .y=framePosition.y - origin.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height}))
	// 	return (false);
	for (const auto& hitbox : this->_hitboxesVec[this->getFrameIndex()]) {
		circleWorld = Tri::convertCircleToWorld(hitbox, framePosition, scale, rotation);
		if (CheckCollisionCircles({circleWorld.x, circleWorld.y}, circleWorld.radius, {circle.x, circle.y}, circle.radius))
			return (true);
	}
	return (false);
}

// bool	Tri::FrameSetHitbox::checkRecCollision(Rectangle rec, Vector2 framePosition, unsigned int frame) {
// 	Vector2	origin = this->getOrigin();
// 	if (frame >= this->getNFrame() || !CheckCollisionRecs(rec, {.x=framePosition.x - origin.x, .y=framePosition.y - origin.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height}))
// 		return (false);
// 	for (const auto& hitbox : this->_hitboxesVec[frame]) {
// 		if (CheckCollisionRecs(rec, {.x=framePosition.x + hitbox.x - origin.x, .y=framePosition.y + hitbox.y - origin.y, .width=hitbox.width, .height=hitbox.height}))
// 			return (true);
// 	}
// 	return (false);
// }

// bool	Tri::FrameSetHitbox::checkRecCollision(Rectangle rec, Vector2 framePosition, float scale) {
// 	Vector2	origin = this->getOrigin();
// 	if (!CheckCollisionRecs(rec, {.x=framePosition.x - (origin.x * scale), .y=framePosition.y - (origin.y * scale), .width=(this->_spriteRectangle.width * scale), .height=(this->_spriteRectangle.height * scale)}))
// 		return (false);
// 	for (const auto& hitbox : this->_hitboxesVec[this->getFrameIndex()]) {
// 		if (CheckCollisionRecs(rec, {.x=framePosition.x + (hitbox.x * scale) - (origin.x * scale), .y=framePosition.y + (hitbox.y * scale) - (origin.y * scale), .width=(hitbox.width * scale), .height=(hitbox.height * scale)}))
// 			return (true);
// 	}
// 	return (false);
// }

// bool	Tri::FrameSetHitbox::checkRecCollision(Rectangle rec, Vector2 framePosition, unsigned int frame, float scale) {
// 	Vector2	origin = this->getOrigin();
// 	if (frame >= this->getNFrame() || !CheckCollisionRecs(rec, {.x=framePosition.x - (origin.x * scale), .y=framePosition.y - (origin.y * scale), .width=(this->_spriteRectangle.width * scale), .height=(this->_spriteRectangle.height * scale)}))
// 		return (false);
// 	for (const auto& hitbox : this->_hitboxesVec[frame]) {
// 		if (CheckCollisionRecs(rec, {.x=framePosition.x + (hitbox.x * scale) - (origin.x * scale), .y=framePosition.y + (hitbox.y * scale) - (origin.y * scale), .width=(hitbox.width * scale), .height=(hitbox.height * scale)}))
// 			return (true);
// 	}
// 	return (false);
// }

//------------------------AnimatedSprite----------------------------//

Tri::AnimatedSprite::AnimatedSprite(std::string spritePath)
: _textureLoaded(false), _nFrameSet(0), _frameSetIndex(0), _cameraSpeed(1.0f)
{
	this->_spriteSheet = LoadTexture(spritePath.c_str());
	if (IsTextureValid(this->_spriteSheet))
	{
		// A. Générer les Mipmaps (les versions plus petites pré-calculées)
        // C'est CRUCIAL pour éviter le scintillement quand l'objet est petit.
        GenTextureMipmaps(&this->_spriteSheet);

        // B. Activer le filtrage TRILINÉAIRE
        // C'est le mode le plus qualitatif en 2D pour lisser les pixels.
        // Il lisse l'agrandissement ET utilise intelligemment les Mipmaps pour le rétrécissement.
        SetTextureFilter(this->_spriteSheet, TEXTURE_FILTER_TRILINEAR);
		this->_textureLoaded = true;
	}
	// this->_frameSets;
	// this->_nFrameSet;
	// this->_frameSetIndex;
	// this->_timer;
	// this->_fps;
}

// Tri::AnimatedSprite::AnimatedSprite(std::string spritePath, float scale)
// : _textureLoaded(false), _nFrameSet(0), _frameSetIndex(0), _scale(scale), _rotation(0), _cameraSpeed(1.0f)
// {
// 	this->_spriteSheet = LoadTexture(spritePath.c_str());
// 	if (IsTextureValid(this->_spriteSheet))
// 		this->_textureLoaded = true;
// 	if (this->_scale < 0)
// 		this->_scale = 0;
// 	// this->_frameSets;
// 	// this->_nFrameSet;
// 	// this->_frameSetIndex;
// 	// this->_timer;
// 	// this->_fps;
// }

Tri::AnimatedSprite::~AnimatedSprite() {
	if (this->_textureLoaded)
		UnloadTexture(this->_spriteSheet);
	this->_textureLoaded = false;
}

void	Tri::AnimatedSprite::draw(Vector2 position, float scale, float rotation, unsigned int indexDelay) {
	if (this->_fps[this->_frameSetIndex] != 0)
	{
		this->_timer[this->_frameSetIndex] += GetFrameTime();
		if (this->_timer[this->_frameSetIndex] >= this->_fps[this->_frameSetIndex])
		{
			this->_timer[this->_frameSetIndex] -= this->_fps[this->_frameSetIndex];
			this->_frameSets[this->_frameSetIndex]++;
		}
	}
	this->_frameSets[this->_frameSetIndex].draw(position, scale, rotation, indexDelay);
	//--------Begin Debug hitbox-------//
	// std::vector<Circle>	circleVec = this->_frameSets[this->_frameSetIndex].getFrameHitboxes();
	// // Vector2	origin = this->_frameSets[this->_frameSetIndex].getOrigin();
	// Vector2 circlePosition;
	// Tri::Circle	circle;
	// float	cameraSpeed = this->_frameSets[this->_frameSetIndex].getCameraSpeed();
	// for (unsigned long i = 0; i < circleVec.size(); i++)
	// {
	// 	circlePosition = Tri::convertCamera(position, cameraSpeed);
	// 	circle = Tri::convertCircleToWorld(circleVec[i], circlePosition, scale, rotation);
	// 	DrawCircle(static_cast<int>(std::round(circle.x)), static_cast<int>(std::round(circle.y)), circle.radius, {255,0,0,127});
	// 	// DrawRectangleRec({circlePosition.x, circlePosition.y, .width=(circleVec[i].width * this->_scale), .height=(circleVec[i].height * this->_scale)}, {255,0,0,127});
	// }
	//--------End Debug hitbox-------//
}

void	Tri::AnimatedSprite::selectFrameSet(unsigned int index) {
	if (index != this->_frameSetIndex && index < this->_nFrameSet)
	{
		this->_frameSets[index].resetFrameIndex();
		this->_timer[index] = 0;
		this->_frameSetIndex = index;
	}
}

// void	Tri::AnimatedSprite::setScale(float scale) {
// 	if (scale > 0)
// 		this->_scale = scale;
// 	else
// 		this->_scale = 0;
// }

// void	Tri::AnimatedSprite::setRotaion(float rotation) {
// 	this->_rotation = rotation;
// }

void	Tri::AnimatedSprite::setCameraSpeed(float cameraSpeedFactor) {
	for (auto& frameSet : this->_frameSets) {
		frameSet.setCameraSpeed(cameraSpeedFactor);
	}
}

// unsigned int	Tri::AnimatedSprite::addFrameSet(Tri::FrameSet frameSet, float fps) {
// 	this->_frameSets.emplace_back(frameSet);
// }

unsigned int	Tri::AnimatedSprite::addFrameSet(Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin, float fps) {
	this->_frameSets.emplace_back(this->_spriteSheet, spriteRectangle, nFrame, origin);
	if (fps > 0)
		this->_fps.emplace_back(1.0 / fps);
	else
		this->_fps.emplace_back(0);
	this->_timer.emplace_back(0);
	return (this->_nFrameSet++);
}

unsigned int	Tri::AnimatedSprite::addFrameSet(Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin, float fps, const std::vector<std::vector<Circle>> &hitboxesVec) {
	this->_frameSets.emplace_back(this->_spriteSheet, spriteRectangle, nFrame, origin, hitboxesVec);
	if (fps > 0)
		this->_fps.push_back(1.0 / fps);
	else
		this->_fps.push_back(0);
	this->_timer.push_back(0);
	return (this->_nFrameSet++);
}

void		Tri::AnimatedSprite::changeFps(unsigned int index, float fps) {
	if (index < this->_nFrameSet)
	{
		if (fps > 0)
			this->_fps[index] = 1.0 / fps;
		else
			this->_fps[index] = 0;
	}
}

Tri::FrameSetHitbox	&Tri::AnimatedSprite::getFrameSet() {
	return (this->_frameSets[this->_frameSetIndex]);
}

// float			Tri::AnimatedSprite::getScale() const {
// 	return (this->_scale);
// }

Vector2			Tri::AnimatedSprite::getOrigin() const {
	return (this->_frameSets[this->_frameSetIndex].getOrigin());
}

unsigned int	Tri::AnimatedSprite::getFrameSetIndex() const {
	return (this->_frameSetIndex);
}

Tri::FrameSetHitbox	&Tri::AnimatedSprite::getFrameSet(unsigned int index) {
	if (index < this->_nFrameSet)
		return (this->_frameSets[index]);
	return (this->_frameSets[this->_nFrameSet]);
}

Texture2D		&Tri::AnimatedSprite::getSpriteSheet() {
	return (this->_spriteSheet);
}

bool	Tri::AnimatedSprite::checkRecCollision(Rectangle rec, Vector2 position, float scale, float rotation) {
	return (this->_frameSets[this->_frameSetIndex].checkRecCollision(rec, position, scale, rotation));	
}

bool	Tri::AnimatedSprite::checkCircleCollision(Tri::Circle circle, Vector2 position, float scale, float rotation) {
	return (this->_frameSets[this->_frameSetIndex].checkCircleCollision(circle, position, scale, rotation));
}

void	Tri::AnimatedSprite::operator++() {
	this->_frameSetIndex = (this->_frameSetIndex + 1) % this->_nFrameSet;
}

void	Tri::AnimatedSprite::operator--() {
	this->_frameSetIndex = this->_frameSetIndex > 0 ? this->_frameSetIndex - 1 : this->_nFrameSet - 1;
}

void	Tri::AnimatedSprite::operator++(int) {
	this->_frameSetIndex = (this->_frameSetIndex + 1) % this->_nFrameSet;
}

void	Tri::AnimatedSprite::operator--(int) {
	this->_frameSetIndex = this->_frameSetIndex > 0 ? this->_frameSetIndex - 1 : this->_nFrameSet - 1;
}
