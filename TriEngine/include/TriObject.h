#ifndef TRI_OBJECT_H
# define TRI_OBJECT_H
# include "TriSprite.h"
# define MAX_SPEED 900.0
# define ACCELERATION_SPEED 2000.0
# define FRICTION 0.98

namespace Tri {
	class Object {
		private:
			Object();
			AnimatedSprite	*_sprite;
		public:
			Object(AnimatedSprite *sprite);
			Object(AnimatedSprite *sprite, Vector2 position);
			Object(AnimatedSprite *sprite, int frameDelay, float scale, float rotation, Vector2 position, float maxSpeed, int type);
			~Object(){};
			std::vector<Circle>	getFrameHitboxes();
			void					setCameraSpeed(float cameraSpeedFactor);
			// float					getScale() const;
			Vector2					getOrigin() const;
			AnimatedSprite			&getSprite();
			void					draw() const;
			bool					checkCollisionRec(Rectangle &rectangle);
			bool					checkCollisionCircle(Tri::Circle &circle);
			bool					checkCollisionObj(Object &object);
			unsigned int			frameDelay;
			float					scale;
			float					rotation;
			Vector2					position;
			Vector2					velocity;
			float					maxSpeed;
			float					accelerationSpeed;
			float					friction;
			int						type;
	};
};

#endif