#include "Camera.h"

void Camera::RegenerateMatrices()
{
	mProjection = glm::perspective(glm::radians(45.0f),
		(float)1280/720,
		0.1f, 100.0f);

	glm::vec3 eye = glm::vec3(4, 3, 3);
	glm::vec3 at = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	mView = glm::lookAt(eye, at, up);

	mRotation = glm::vec3(0, 0, 0);
	mPosition = glm::vec3(0, 0, 0);
}

void Camera::SetCameraLocation(float x, float y, float z)
{
	mPosition = glm::vec3(x, y, z);
	mView = glm::translate(mView, mPosition);
}

void Camera::SetCameraRotation(float x, float y, float z)
{
	mRotation = glm::vec3(x, y, z);
	mView = glm::rotate(mView, glm::radians(x), glm::vec3(1, 0, 0));
	mView = glm::rotate(mView, glm::radians(y), glm::vec3(0, 1, 0));
	mView = glm::rotate(mView, glm::radians(z), glm::vec3(0, 0, 1));
}

void Camera::AdjustCameraLocation(float x, float y, float z)
{
	mPosition += glm::vec3(x, y, z);
	mView = glm::translate(mView, mPosition);
}

void Camera::AdjustCameraRotation(float x, float y, float z)
{
	mRotation += glm::vec3(x, y, z);
	mView = glm::rotate(mView, glm::radians(mRotation.x), glm::vec3(1, 0, 0));
	mView = glm::rotate(mView, glm::radians(mRotation.y), glm::vec3(0, 1, 0));
	mView = glm::rotate(mView, glm::radians(mRotation.z), glm::vec3(0, 0, 1));
}
