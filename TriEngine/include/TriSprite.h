#ifndef TRI_SPRITE_H
# define TRI_SPRITE_H
# include "../../lib/raylib/src/raylib.h"
# include <vector>

namespace Tri {
	class Sprite
	{
		private:
			Sprite();
			Texture2D		&_spriteSheet;
			Rectangle		_spriteRectangle;
			unsigned int	_nFrame;
			Vector2			_origin;
			unsigned int	_frameIndex;
		public:
			Sprite(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrames);
			Sprite(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrames, Vector2 origin);
			~Sprite(){};
			void	setOrigin(Vector2 origin);
			void	setOriginToCenter();
			void	setFrameIndex(unsigned int index);
			unsigned int	getNFrame() const;
			unsigned int	getFrameIndex() const;
			void	draw(Vector2 position, float scale) const;
			void	draw(Vector2 position, float scale, float rotation) const;
			void	draw(Vector2 position, float scale, float rotation, unsigned int index) const;
			void	drawDeformed(Rectangle dest) const;
			void	drawDeformed(Rectangle dest, float rotation) const;
			void	drawDeformed(Rectangle dest, float rotation, unsigned int index) const;
			void	addFrameIndex();
			void	addFrameIndex(unsigned int value);
			void	susFrameIndex();
			void	susFrameIndex(unsigned int value);
			void	operator++();
			void	operator--();
			void	operator++(int);
			void	operator--(int);
	};

	class SpriteHitbox : public Sprite
	{
		private:
			SpriteHitbox();
			std::vector<std::vector<Rectangle>>	hitBoxVec;
		public:
			SpriteHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrames);
			SpriteHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrames, Vector2 origin);
			SpriteHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrames, std::vector<std::vector<Rectangle>> hitBoxVec);
			SpriteHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrames, Vector2 origin, std::vector<std::vector<Rectangle>> hitBoxVec);
			~SpriteHitbox(){};
			std::vector<Rectangle>	getFrameHitBox() const;
			std::vector<Rectangle>	getFrameHitBox(unsigned int index) const;
			void					addHitboxToFrame(unsigned int index, Rectangle hitBox);
			bool					checkRecCollision(Rectangle rec);
			bool					checkRecCollision(Rectangle rec, unsigned int frame);
			bool					checkRecCollision(Tri::SpriteHitbox source);
			bool					checkRecCollision(Tri::SpriteHitbox source, unsigned int frame);
			bool					checkRecCollision(Tri::SpriteHitbox source, unsigned int sourceFrame, unsigned int frame);
	};
};
#endif