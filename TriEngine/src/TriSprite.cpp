#include "../include/TriSprite.h"
#include <iostream>

Tri::Sprite::Sprite(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame)
: _spriteSheet(spriteSheet), _spriteRectangle(spriteRectangle), _nFrame(nFrame), _origin({0, 0}), _frameIndex(0) {
}

Tri::Sprite::Sprite(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin)
: _spriteSheet(spriteSheet), _spriteRectangle(spriteRectangle), _nFrame(nFrame), _origin(origin), _frameIndex(0) {
}


// Tri::Sprite::~Sprite() {

// }

void	Tri::Sprite::setOrigin(Vector2 origin) {
	this->_origin = origin;
}

void	Tri::Sprite::setOriginToCenter() {
	this->_origin.x = this->_spriteRectangle.width / 2.0;
	this->_origin.y = this->_spriteRectangle.height / 2.0;
}

void	Tri::Sprite::setFrameIndex(unsigned int index) {
	this->_frameIndex = index % this->_nFrame;
}

unsigned int	Tri::Sprite::getFrameIndex() const {
	return (this->_frameIndex);
}


unsigned int	Tri::Sprite::getNFrame() const {
	return this->_nFrame;
}

void	Tri::Sprite::draw(Vector2 position, float scale) const {
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};
	Rectangle	dest = {.x=position.x, .y= position.y, .width=this->_spriteRectangle.width * scale, .height=this->_spriteRectangle.height * scale};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * scale, this->_origin.y * scale}, 0, WHITE);
}

void	Tri::Sprite::drawDeformed(Rectangle dest) const {
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * (dest.width / source.width), this->_origin.y * (dest.height / source.height)}, 0, WHITE);
}

void	Tri::Sprite::draw(Vector2 position, float scale, float rotation) const {
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};
	Rectangle	dest = {.x=position.x, .y= position.y, .width=this->_spriteRectangle.width * scale, .height=this->_spriteRectangle.height * scale};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * scale, this->_origin.y * scale}, rotation, WHITE);
}

void	Tri::Sprite::drawDeformed(Rectangle dest, float rotation) const {
	Rectangle	source = {.x=this->_spriteRectangle.x + (this->_frameIndex * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * (dest.width / source.width), this->_origin.y * (dest.height / source.height)}, rotation, WHITE);
}

void	Tri::Sprite::draw(Vector2 position, float scale, float rotation, unsigned int index) const {
	Rectangle	source = {.x=this->_spriteRectangle.x + (index % this->_nFrame * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};
	Rectangle	dest = {.x=position.x, .y= position.y, .width=this->_spriteRectangle.width * scale, .height=this->_spriteRectangle.height * scale};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * scale, this->_origin.y * scale}, rotation, WHITE);
}

void	Tri::Sprite::drawDeformed(Rectangle dest, float rotation, unsigned int index) const {
	Rectangle	source = {.x=this->_spriteRectangle.x + (index % this->_nFrame * this->_spriteRectangle.width), .y=this->_spriteRectangle.y, .width=this->_spriteRectangle.width, .height=this->_spriteRectangle.height};

	DrawTexturePro(this->_spriteSheet, source, dest, (Vector2){this->_origin.x * (dest.width / source.width), this->_origin.y * (dest.height / source.height)}, rotation, WHITE);
}

void	Tri::Sprite::addFrameIndex() {
	this->_frameIndex = (this->_frameIndex + 1) % this->_nFrame;
}
void	Tri::Sprite::addFrameIndex(unsigned int value) {
	this->_frameIndex = (this->_frameIndex + value) % this->_nFrame;
}
void	Tri::Sprite::susFrameIndex() {
	this->_frameIndex = this->_frameIndex > 0 ? this->_frameIndex - 1 : this->_nFrame - 1;
}
void	Tri::Sprite::susFrameIndex(unsigned int value) {
	this->_frameIndex = (value % this->_nFrame) > this->_frameIndex ? this->_nFrame - (value % this->_nFrame) - this->_frameIndex : this->_frameIndex - (value % this->_nFrame);
}

void	Tri::Sprite::operator++() {
	this->addFrameIndex();
}

void	Tri::Sprite::operator--() {
	this->susFrameIndex();
}

void	Tri::Sprite::operator++(int) {
	this->addFrameIndex();
}

void	Tri::Sprite::operator--(int) {
	this->susFrameIndex();
}
