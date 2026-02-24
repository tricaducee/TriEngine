#ifndef TRI_CAMERA_H
# define TRI_CAMERA_H
# include "../../lib/raylib/src/raylib.h"

namespace Tri {
	class Camera {
		private:
		Camera();
		Rectangle	_cameraRec;
		Vector2		_origin;
		Vector2		_position;
		public:
		Camera(Vector2 position);
		~Camera(){};
		Rectangle	getCameraRec() const;
		Rectangle	getSpeededCameraRec(float speedFactor) const;
		Vector2	getPosition() const;
		void	setPosition(Vector2 position);
		Vector2	convertPosition(Vector2 position, float factor);
		void	refreshCamera();
	};

	Vector2	convertCamera(Vector2 position, float factor);
	Camera	&camera();
	void	drawRectangleCamera(Rectangle rectangle, float camSpeedFactor, Color color);
};

#endif