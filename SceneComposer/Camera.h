#pragma once
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
	friend class Graphics;
	friend class Application;
public:
	Camera() = default;

private:
	inline glm::mat4 GetViewMatrix() const noexcept { return mView; }
	inline glm::mat4 GetProjectionMatrix() const noexcept { return mProjection; }

public:
	void RegenerateMatrices();
	inline glm::vec3 GetCameraPosition() const noexcept { return mPosition; }
	inline glm::vec3 GetCameraRotation() const noexcept { return mRotation; }

	void SetCameraLocation(float x, float y, float z);
	void SetCameraRotation(float x, float y, float z);

	void AdjustCameraLocation(float x, float y, float z);
	void AdjustCameraRotation(float x, float y, float z);

private:
	glm::vec3 mPosition, mRotation;
	glm::mat4 mView;
	glm::mat4 mProjection;
};
