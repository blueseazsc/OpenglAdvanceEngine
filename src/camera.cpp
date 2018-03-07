#include "camera.h"

using namespace framework;
Camera::Camera() : mPos(10.0f, 10.0f, 10.0f), mViewCenter(0.0f, 0.0f, 0.0f), mUp(0.0f, 1.0f, 0.0f) 
{
	mbMoveLeft = mbMoveRight = mbMoveForward = mbMoveBack = false;
}
void Camera::Update(float deltaTime, glm::mat4 &viewMatrix) {
	float moveSpeed = 10.0f;
	Vector3f forwardDirection = mViewCenter - mPos;
	forwardDirection.normalize();
	Vector3f rightDirection = CrossProduct(forwardDirection, mUp);
	rightDirection.normalize();
	if (mbMoveLeft) {
		Vector3f delta = rightDirection*deltaTime*moveSpeed;
		mPos = mPos - delta;
		mViewCenter = mViewCenter - delta;
	}
	if (mbMoveRight) {
		Vector3f delta = rightDirection*deltaTime*moveSpeed;
		mPos = mPos + delta;
		mViewCenter = mViewCenter + delta;
	}
	if (mbMoveForward) {
		Vector3f delta = forwardDirection*deltaTime*moveSpeed;
		mPos = mPos + delta;
		mViewCenter = mViewCenter + delta;
	}
	if (mbMoveBack) {
		Vector3f delta = forwardDirection*deltaTime*moveSpeed;
		mPos = mPos - delta;
		mViewCenter = mViewCenter - delta;
	}
	viewMatrix = glm::lookAt(
			glm::vec3(mPos.x, mPos.y, mPos.z), 
			glm::vec3(mViewCenter.x, mViewCenter.y, mViewCenter.z), 
			glm::vec3(mUp.x, mUp.y, mUp.z)
			);
}
void Camera::Pitch(float angle) {
	Vector3f forwardDirection = mViewCenter - mPos;
	forwardDirection.normalize();
	Vector3f rightDirection = CrossProduct(forwardDirection, mUp);
	rightDirection.normalize();
	RotateView(angle, rightDirection.x, rightDirection.y, rightDirection.z);
}
void Camera::Yaw(float angle) {
	RotateView(angle, mUp.x, mUp.y, mUp.z);
}
void Camera::RotateView(float angle, float x, float y, float z) {
	Vector3f viewDirection = mViewCenter - mPos;
	Vector3f newDirection(0.0f, 0.0f, 0.0f);
	float C = cosf(angle);
	float S = sinf(angle);
	Vector3f tempX(C + x*x*(1 - C), x*y*(1 - C) - z*S, x*z*(1 - C) + y*S);
	newDirection.x = tempX*viewDirection;
	Vector3f tempY(x*y*(1 - C) + z*S, C + y*y*(1 - C), y*z*(1 - C) - x*S);
	newDirection.y = tempY*viewDirection;
	Vector3f tempZ(x*z*(1 - C) - y*S, y*z*(1 - C) + x*S, C + z*z*(1 - C));
	newDirection.z = tempZ*viewDirection;
	mViewCenter = mPos + newDirection;
}
void Camera::SwitchTo3D(glm::mat4 &projectionMatrix) {
	projectionMatrix = glm::perspective(60.f, (float)mViewportWidth / (float)mViewportHeight, 0.1f, 1000.f);
}
void Camera::SwitchTo2D(glm::mat4 &projectionMatrix) {
	projectionMatrix = glm::ortho(-mViewportWidth / 2, mViewportWidth / 2, -mViewportHeight / 2, mViewportHeight / 2);
}
