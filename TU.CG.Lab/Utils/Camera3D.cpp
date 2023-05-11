#include "Camera3D.hpp"

#include <algorithm>
#include <glm/ext/matrix_transform.hpp>

namespace Utils
{
	Camera3D::Camera3D(
		const glm::vec3 position, const glm::vec3 worldUp, const float maxZoom)
		:
		position(position), front(0.0f, 0.0f, -1.0f), up(), right(), worldUp(worldUp),
		yaw(-90.0f), pitch(0.0f), movementSpeed(2.5f), mouseSensitivity(0.1f),
		previousCursorPosition(0.0f), zoom(maxZoom), maxZoom(maxZoom),
		isUserControlEnabled(true)
	{
	}

	glm::mat4 Camera3D::GetViewMatrix() const
	{
		return glm::lookAt(position, position + front, up);
	}

	void Camera3D::Update(const float deltaTime, Input::InputManager& inputManager)
	{
		if (!isUserControlEnabled)
			return;

		const auto velocity = movementSpeed * deltaTime;
		const auto forwardBackwardMovement = front * velocity;
		const auto leftRightMovement = right * velocity;

		if (inputManager.IsKeyDown(Input::Keys::W))
			position += forwardBackwardMovement;
		if (inputManager.IsKeyDown(Input::Keys::S))
			position -= forwardBackwardMovement;
		if (inputManager.IsKeyDown(Input::Keys::A))
			position -= leftRightMovement;
		if (inputManager.IsKeyDown(Input::Keys::D))
			position += leftRightMovement;

		const auto currentCursorPos = inputManager.GetCursorPosition();

		auto xOffset = currentCursorPos.x - previousCursorPosition.x;
		auto yOffset = previousCursorPosition.y - currentCursorPos.y;

		previousCursorPosition = currentCursorPos;

		xOffset *= mouseSensitivity;
		yOffset *= mouseSensitivity;

		yaw += xOffset;
		pitch += yOffset;

		pitch = std::clamp(pitch, -89.0f, 89.0f);

		const auto yawRadians = glm::radians(yaw);
		const auto pitchRadians = glm::radians(pitch);

		front.x = cos(yawRadians) * cos(pitchRadians);
		front.y = sin(pitchRadians);
		front.z = sin(yawRadians) * cos(pitchRadians);

		front = glm::normalize(front);
		right = glm::normalize(glm::cross(front, worldUp));
		up = glm::normalize(glm::cross(right, front));

		zoom -= inputManager.GetScrollValue();
		zoom = std::clamp(zoom, 1.0f, maxZoom);
	}
}
