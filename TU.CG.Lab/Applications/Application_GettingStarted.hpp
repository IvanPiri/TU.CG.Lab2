#pragma once

#include <memory>

#include "IApplication.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/VertexArray.hpp"
#include "Utils/Camera3D.hpp"
#include "Utils/Window.hpp"

namespace Applications
{
	class Application_GettingStarted : public IApplication
	{
		private:
			unsigned boxTexture;
			unsigned faceTexture;
		protected:
			Input::InputManager inputManager;

			std::unique_ptr<Utils::Window> window;
			std::unique_ptr<Utils::Camera3D> camera;
			std::unique_ptr<Graphics::ShaderProgram> shader;
			std::unique_ptr<Graphics::VertexArray> va;

			void Initialize();
			void LoadContent();
			void UnloadContent();
			void Update(float deltaTime);
			void Render() const;
		public:
			Application_GettingStarted();

			void Run();

			Input::InputManager& GetInputManager() override
			{
				return inputManager;
			}
	};
}
