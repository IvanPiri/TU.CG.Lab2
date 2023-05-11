#pragma once

#include <exception>
#include <glm/glm.hpp>

namespace Applications
{
	class IApplication;
}

struct GLFWwindow;

namespace Utils
{
	class Window
	{
		private:
			GLFWwindow* window;

			static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);
			static void KeyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods);
			static void CursorPosCallback(GLFWwindow* window, double x, double y);
			static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
			static void ScrollCallback(GLFWwindow* window, double x, double y);

			static std::exception GetUserPointerNullException();
		public:
			Window(const char* title, int width, int height);
			Window(const Window& other) = delete;
			Window& operator=(const Window& other) = delete;
			Window(Window&& other) = delete;
			Window& operator=(Window&& other) = delete;
			~Window();

			void InitOpenGL() const;
			void SwapBuffers() const;
			void PollEvents();
			void ActivateInputFor(Applications::IApplication* app) const;

			[[nodiscard]] bool GetShouldClose() const;
			void SetShouldClose(bool value) const;

			[[nodiscard]] float GetElapsedTime() const;
			[[nodiscard]] glm::vec2 GetSize() const;
	};
}
