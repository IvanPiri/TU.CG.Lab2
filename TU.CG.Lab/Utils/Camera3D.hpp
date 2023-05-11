#pragma once

#include <glm/glm.hpp>

#include "Input/InputManager.hpp"

namespace Utils
{
	class Camera3D
	{
		private:
			glm::vec3 position;
			glm::vec3 front;
			glm::vec3 up;
			glm::vec3 right;
			glm::vec3 worldUp;

			float yaw;
			float pitch;

			float movementSpeed;
			float mouseSensitivity;

			glm::vec2 previousCursorPosition;

			float zoom;
			const float maxZoom;

			bool isUserControlEnabled;
		public:
			Camera3D(glm::vec3 position, glm::vec3 worldUp, float maxZoom);

			void Update(float deltaTime, Input::InputManager& inputManager);

			void SetIsUserControlEnabled(const bool value) { isUserControlEnabled = value; }
			void SetPosition(const glm::vec3& newPosition) { position = newPosition; }
			void SetFront(const glm::vec3& newFront) { front = newFront; }
			void SetWorldUp(const glm::vec3& newWorldUp) { worldUp = newWorldUp; }
			void SetZoom(const float newZoom) { zoom = newZoom; }
			void SetMovementSpeed(const float newMovementSpeed) { movementSpeed = newMovementSpeed; }
			void SetMouseSensitivity(const float newMouseSensitivity) { mouseSensitivity = newMouseSensitivity; }

			[[nodiscard]] glm::mat4 GetViewMatrix() const;

			[[nodiscard]] bool GetIsUserControlEnabled() const { return isUserControlEnabled; }
			[[nodiscard]] glm::vec3 GetPosition() const { return position; }
			[[nodiscard]] glm::vec3 GetFront() const { return front; }
			[[nodiscard]] glm::vec3 GetWorldUp() const { return worldUp; }
			[[nodiscard]] float GetZoom() const { return zoom; }
			[[nodiscard]] float GetMovementSpeed() const { return movementSpeed; }
			[[nodiscard]] float GetMouseSensitivity() const { return mouseSensitivity; }
	};
}
