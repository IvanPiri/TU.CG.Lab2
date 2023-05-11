#include "Window.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Applications/IApplication.hpp"

namespace Utils
{
	Window::Window(const char* title, const int width, const int height)
	{
		if (width <= 0)
			throw std::exception("Screen width must be a positive integer.");
		if (height <= 0)
			throw std::exception("Screen height must be a positive integer.");
		if (glfwInit() != GLFW_TRUE)
			throw std::exception("Failed to initialize GLFW.");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		window = glfwCreateWindow(width, height, "TU.CG.Lab", nullptr, nullptr);

		if (window == nullptr)
		{
			glfwTerminate();
			throw std::exception("Failed to create a GLFW window.");
		}

		InitOpenGL();

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glfwTerminate();
			throw std::exception("Failed to initialize GLAD.");
		}

		glViewport(0, 0, width, height);
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	void Window::InitOpenGL() const
	{
		glfwMakeContextCurrent(window);
	}

	void Window::SwapBuffers() const
	{
		glfwSwapBuffers(window);
	}

	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::ActivateInputFor(Applications::IApplication* app) const
	{
		glfwSetWindowUserPointer(window, app);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		glfwSetFramebufferSizeCallback(window, FramebufferSizeCallback);
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetCursorPosCallback(window, CursorPosCallback);
		glfwSetScrollCallback(window, ScrollCallback);
	}

	bool Window::GetShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void Window::SetShouldClose(const bool value) const
	{
		glfwSetWindowShouldClose(window, value);
	}

	float Window::GetElapsedTime() const
	{
		return static_cast<float>(glfwGetTime());
	}

	glm::vec2 Window::GetSize() const
	{
		int width = 0;
		int height = 0;
		glfwGetWindowSize(window, &width, &height);

		return glm::vec2(width, height);
	}

	void Window::FramebufferSizeCallback(
		GLFWwindow* window, const int width, const int height)
	{
		glViewport(0, 0, width, height);
	}

	void Window::KeyCallback(
		GLFWwindow* window, int key, int scanCode, int action, int mods)
	{
		const auto userDataPointer = glfwGetWindowUserPointer(window);

		if (userDataPointer == nullptr)
			throw GetUserPointerNullException();

		const auto app = static_cast<Applications::IApplication*>(userDataPointer);
		const auto ourKey = static_cast<Input::Keys>(key);

		switch (action)
		{
			case GLFW_PRESS:
			case GLFW_REPEAT:
			{
				app->GetInputManager().PressKey(ourKey);
				break;
			}
			case GLFW_RELEASE:
			{
				app->GetInputManager().ReleaseKey(ourKey);
				break;
			}
			default:
			{
				break;
			}
		}
	}

	void Window::CursorPosCallback(GLFWwindow* window, double x, double y)
	{
		const auto userDataPointer = glfwGetWindowUserPointer(window);

		if (userDataPointer == nullptr)
			throw GetUserPointerNullException();

		const auto app = static_cast<Applications::IApplication*>(userDataPointer);

		app->GetInputManager().SetCursorPosition(
			static_cast<float>(x), static_cast<float>(y));
	}

	void Window::MouseButtonCallback(
		GLFWwindow* window, int button, int action, int mods)
	{
		const auto userDataPointer = glfwGetWindowUserPointer(window);

		if (userDataPointer == nullptr)
			throw GetUserPointerNullException();

		const auto app = static_cast<Applications::IApplication*>(userDataPointer);
		const auto ourButton = static_cast<Input::MouseButtons>(button);

		switch (action)
		{
			case GLFW_PRESS:
			case GLFW_REPEAT:
			{
				app->GetInputManager().PressButton(ourButton);
				break;
			}
			case GLFW_RELEASE:
			{
				app->GetInputManager().ReleaseButton(ourButton);
				break;
			}
			default:
			{
				break;
			}
		}
	}

	void Window::ScrollCallback(GLFWwindow* window, double x, double y)
	{
		const auto userDataPointer = glfwGetWindowUserPointer(window);

		if (userDataPointer == nullptr)
			throw GetUserPointerNullException();

		const auto app = static_cast<Applications::IApplication*>(userDataPointer);

		app->GetInputManager().Scroll(static_cast<float>(y));
	}

	std::exception Window::GetUserPointerNullException()
	{
		return std::exception("GLFW user data pointer cannot be null.");
	}
}
