#ifndef TRI_CLASS_H
# define TRI_CLASS_H
# include "../../lib/raylib/src/raylib.h"

namespace Tri {
	struct Circle {
		float	x;
		float	y;
		float	radius;
	};

	Circle	convertCircleToWorld(Circle circle, Vector2 position, float scale, float rotation);
};

#endif