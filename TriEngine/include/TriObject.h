#ifndef TRI_OBJECT_H
# define TRI_OBJECT_H
# include "TriSprite.h"

namespace Tri {
	class Object {
		private:
			Object();
			AnimatedSprite	&_sprite;
		public:
			Object(AnimatedSprite &sprite);
			Object(AnimatedSprite &sprite, Vector2 position);
			~Object(){};
			std::vector<Rectangle>	getFrameHitboxes();
			void					setCameraSpeed(float cameraSpeedFactor);
			float	getScale() const;
			Vector2	getOrigin() const;
			AnimatedSprite	&getSprite();
			void			draw() const;
			bool	checkCollisionRec(Rectangle &rectangle);
			bool	checkCollisionObj(Object &object);
			Vector2	position;
			Vector2	acceleration;
	};
};

#endif