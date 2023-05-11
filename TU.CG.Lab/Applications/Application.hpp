#pragma once

#include <memory>

#include "IApplication.hpp"
#include "Graphics/Model.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/VertexArray.hpp"
#include "Input/InputManager.hpp"
#include "Utils/Camera3D.hpp"
#include "Utils/ContentManager.hpp"
#include "Utils/Window.hpp"

namespace Applications
{
	class Application : public IApplication
	{
		private:
			glm::vec3 lightPos;
		protected:
			Input::InputManager inputManager;
			Utils::ContentManager content;

			std::unique_ptr<Utils::Camera3D> camera;
			std::unique_ptr<Utils::Window> window;
			std::unique_ptr<Graphics::ShaderProgram> lightShader;
			std::unique_ptr<Graphics::ShaderProgram> modelShader;
			std::unique_ptr<Graphics::VertexArray> lightVa;
			std::unique_ptr<Graphics::Model> backpack;

			void Initialize();
			void LoadContent();
			void UnloadContent();
			void Update(float deltaTime);
			void Render();
		public:
			Application();

			void Run();

			Input::InputManager& GetInputManager() override { return inputManager; }
	};
}
