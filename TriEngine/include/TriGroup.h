#ifndef TRI_GROUP_H
# define TRI_GROUP_H
# include "TriObject.h"
# include "TriCamera.h"
# include <utility>

namespace Tri {
	class Group {
		private:
		Rectangle									_hitbox;
		// std::vector<Color>							_colorVec;
		std::vector<Object>							_objVec;
		std::vector<Group*>							_groupVec;
		public:
			Group();
			Group(Rectangle hitbox);
			~Group(){};
			void		addObject(AnimatedSprite *sprite, int frameDelay, float scale, float rotation, Vector2 position, float maxSpeed, int type);
			void		addGroup(Group *group);
			void		setCameraSpeed(float cameraSpeedFactor);
			Rectangle	getHitboxRectangle() const;
			bool		checkGroupCollision(Rectangle &rectangle);
			bool		checkGroupCollision(Object &object);
			// Rectangle	checkGroupCollisionRecs(Object &object);
			bool		checkGroupCollision(Group &group);
			int			supCollidedObj(Object &object);
			bool		checkGroupCollisionAll(Rectangle &rectangle);
			bool		checkGroupCollisionAll(Object &object);
			bool		checkGroupCollisionAll(Group &group);
			void		draw();
			void		findHitbox();
			float		cameraSpeed;
	};
};

#endif