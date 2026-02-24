#ifndef TRI_GRAVITY_H
# define TRI_GRAVITY_H
# define TRI_GRAVITY 2.0f
# include "TriGroup.h"

namespace Tri {
	class Gravity {
		private:
			Gravity();
			Vector2	_direction;
			float	_gravity;
			float	_deltaTime;
		public:
			Gravity(Vector2 direction);
			Gravity(Vector2 direction, float gravity);
			~Gravity(){};
			void	applyGravity(Vector2 &position, Vector2 &acceleration);
			void	applyGravityCollision(Object &obj, Group &group);
			void	applyGravityCollision(Rectangle &rectangle, Vector2 &acceleration, Group &group);
	};
}
#endif