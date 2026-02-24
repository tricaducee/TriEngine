#ifndef TRI_GROUP_H
# define TRI_GROUP_H
# include "TriObject.h"
# include "TriCamera.h"
# include <utility>

namespace Tri {
	class Group {
		private:
		Rectangle									_hitbox;
		std::vector<std::pair<Rectangle*, Color>>	_recVec;
		std::vector<Color>							_colorVec;
		std::vector<Object*>						_objVec;
		std::vector<Group*>							_groupVec;
		public:
			Group();
			Group(Rectangle hitbox);
			~Group(){};
			void		addRectangle(Rectangle *rectangle, Color color);
			void		addObject(Object *object);
			void		addGroup(Group *group);
			void		setCameraSpeed(float cameraSpeedFactor);
			Rectangle	getHitboxRectangle() const;
			bool		checkGroupCollision(Rectangle &rectangle);
			bool		checkGroupCollision(Object &object);
			bool		checkGroupCollision(Group &group);
			bool		checkGroupCollisionAll(Rectangle &rectangle);
			bool		checkGroupCollisionAll(Object &object);
			bool		checkGroupCollisionAll(Group &group);
			void		draw();
			void		findHitbox();
			float		cameraSpeed;
	};
};

#endif