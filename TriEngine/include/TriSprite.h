#ifndef TRI_SPRITE_H
# define TRI_SPRITE_H
# include "../../lib/raylib/src/raylib.h"
# include <vector>
# include <string>
# include "TriClass.h"

namespace Tri {
	class FrameSet
	{
		private:
			FrameSet();
			Texture2D		&_spriteSheet;
			unsigned int	_nFrame;
			Vector2			_origin;
			unsigned int	_frameIndex;
			unsigned int	_initStartIndex;
			bool			_inCamera;
			float			_cameraSpeed;

		protected:
			Rectangle		_spriteRectangle;

		public:
			FrameSet(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame);
			FrameSet(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin);
			~FrameSet(){};
			void	setOrigin(Vector2 origin);
			void	setOriginToCenter();
			void	setFrameIndex(unsigned int index);
			void	resetFrameIndex();
			void	setInitStartIndex(unsigned int start);
			void	setCameraSpeed(float speed);
			void	setInCamera(bool inCamera);
			unsigned int	getNFrame() const;
			unsigned int	getFrameIndex() const;
			Vector2			getOrigin() const;
			Rectangle		getSpriteRectangle() const;
			float			getCameraSpeed() const;
			void	draw(Vector2 position) const;
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

	class FrameSetHitbox : public FrameSet
	{
		private:
			FrameSetHitbox();
			std::vector<std::vector<Tri::Circle>>	_hitboxesVec;
		public:
			FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame);
			FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin);
			FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, std::vector<std::vector<Circle>> hitboxesVec);
			FrameSetHitbox(Texture2D &spriteSheet, Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin, std::vector<std::vector<Circle>> hitboxesVec);
			~FrameSetHitbox(){};
			std::vector<Tri::Circle>	getFrameHitboxes() const;
			std::vector<Tri::Circle>	getFrameHitboxes(unsigned int index) const;
			void					addHitboxToFrame(unsigned int index, Circle hitBox);
			bool					checkRecCollision(Rectangle rec, Vector2 framePosition, float scale, float rotation);
			bool					checkCircleCollision(Circle circle, Vector2 framePosition, float scale, float rotation);
			// bool					checkRecCollision(Rectangle rec, Vector2 framePosition);
			// bool					checkRecCollision(Rectangle rec, Vector2 framePosition, unsigned int frame);
			// bool					checkRecCollision(Rectangle rec, Vector2 framePosition, float scale);
			// bool					checkRecCollision(Rectangle rec, Vector2 framePosition, unsigned int frame, float scale);
	};

	class AnimatedSprite
	{
		private:
			AnimatedSprite();
			Texture2D					_spriteSheet;
			bool						_textureLoaded;
			std::vector<FrameSetHitbox>	_frameSets;
			unsigned int				_nFrameSet;
			unsigned int				_frameSetIndex;
			std::vector<double>			_timer;
			std::vector<float>			_fps;
			float						_cameraSpeed;
		public:
			AnimatedSprite(std::string spritePath);
			~AnimatedSprite();
			// void	draw(Vector2 position);
			void	draw(Vector2 position, float scale, float rotation, unsigned int indexDelay);
			void	selectFrameSet(unsigned int index);
			// void	setScale(float scale);
			// void	setRotaion(float rotation);
			void	setCameraSpeed(float cameraSpeedFactor);
			// unsigned int	addFrameSet(FrameSet frameSet, float fps);
			unsigned int	addFrameSet(Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin, float fps);
			unsigned int	addFrameSet(Rectangle spriteRectangle, unsigned int nFrame, Vector2 origin, float fps, const std::vector<std::vector<Circle>> &hitboxesVec);
			Texture2D		&getSpriteSheet();
			FrameSetHitbox	&getFrameSet();
			FrameSetHitbox	&getFrameSet(unsigned int index);
			// float			getScale() const;
			Vector2			getOrigin() const;
			unsigned int	getFrameSetIndex() const;
			bool			checkRecCollision(Rectangle rec, Vector2 position, float scale, float rotation);
			bool			checkCircleCollision(Circle rec, Vector2 position, float scale, float rotation);
			void		changeFps(unsigned int index, float fps);
			void	operator++();
			void	operator--();
			void	operator++(int);
			void	operator--(int);
	};
};
#endif