#ifndef CAMERA_H
#define CAMERA_H

#include "header.h"
#include "vector3.h"

namespace framework {

class Camera {
public:
	Camera();
	void Update(float deltaTime, glm::mat4 &viewMatrix);
	void Pitch(float angle);
	void Yaw(float angle);
	void RotateView(float angle, float x, float y, float z);
	void SwitchTo2D(glm::mat4 &projectionMatrix);
	void SwitchTo3D(glm::mat4 &projectionMatrix);
public:
	Vector3f  mPos, mViewCenter, mUp;
	bool mbMoveLeft, mbMoveRight, mbMoveForward, mbMoveBack;
	int mViewportWidth, mViewportHeight;
};
}
#endif
