#include "Application.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <string>

namespace Applications
{
	Application::Application() : lightPos(1.2f, 1.0f, 2.0f)
	{
		window = std::make_unique<Utils::Window>("TU.CG.Lab", 800, 600);
	}

	void Application::Run()
	{
		auto lastFrame = 0.0f;

		Initialize();
		LoadContent();

		while (!window->GetShouldClose())
		{
			const auto currentFrame = window->GetElapsedTime();
			const auto deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			Update(deltaTime);
			Render();

			window->SwapBuffers();
			window->PollEvents();
		}

		UnloadContent();
	}

	void Application::Initialize()
	{
		window->ActivateInputFor(this);

		camera = std::make_unique<Utils::Camera3D>(
			glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);

		glEnable(GL_DEPTH_TEST);
	}

	void Application::LoadContent()
	{
		//
		// ------ Models
		//

		backpack = content.GetModel("Content/Models/backpack/backpack.wfobj");

		constexpr float lightVertices[] =
		{
			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,

			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,

			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,

			-0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f, -0.5f,
			 0.5f, -0.5f,  0.5f,
			 0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f,  0.5f,
			-0.5f, -0.5f, -0.5f,

			-0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f, -0.5f,
			 0.5f,  0.5f,  0.5f,
			 0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f,  0.5f,
			-0.5f,  0.5f, -0.5f,
		};

		lightVa = std::make_unique<Graphics::VertexArray>();

		auto lightVb = std::make_unique<Graphics::VertexBuffer>(
			lightVertices, sizeof lightVertices);

		lightVb->SetAttributes({
			{"aPos", Graphics::VertexAttributeType::VEC3F},
		});

		lightVa->SetVertexBuffer(std::move(lightVb));

		//
		// ------ Shaders
		//

		modelShader = content.GetShader(
			"Content/Shaders/model_loading.vert",
			"Content/Shaders/model_loading.frag");

		lightShader = content.GetShader(
			"Content/Shaders/light_box.vert",
			"Content/Shaders/light_box.frag");

		modelShader->Use();

		modelShader->SetFloat("material.shininess", 128.0f);
		modelShader->SetVec3f("light.position", lightPos);
		modelShader->SetVec3f("light.ambient", glm::vec3(0.2f));
		modelShader->SetVec3f("light.diffuse", glm::vec3(0.5f));
		modelShader->SetVec3f("light.specular", glm::vec3(1.0f));

		modelShader->Unuse();
	}

	void Application::UnloadContent()
	{
		modelShader = nullptr;
		backpack = nullptr;
		lightShader = nullptr;
		lightVa = nullptr;
		content.Clear();
	}

	void Application::Update(const float deltaTime)
	{
		if (inputManager.IsKeyDown(Input::Keys::ESCAPE))
			window->SetShouldClose(true);

		camera->Update(deltaTime, inputManager);

		inputManager.ResetState();
	}

	void Application::Render()
	{
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto model = glm::mat4(1.0f);

		const auto view = camera->GetViewMatrix();

		const auto windowSize = window->GetSize();

		const auto projection = glm::perspective(
			glm::radians(camera->GetZoom()), windowSize.x / windowSize.y, 0.1f, 100.0f);

		const auto normal = glm::inverseTranspose(glm::mat3(model));

		constexpr auto radius = 4.0f;
		const auto time = window->GetElapsedTime();
		const auto lightX = sin(time) * radius;
		const auto lightZ = cos(time) * radius;

		lightPos.x = lightX;
		lightPos.z = lightZ;

		modelShader->Use();

		modelShader->SetMat4f("model", model);
		modelShader->SetMat4f("view", view);
		modelShader->SetMat4f("projection", projection);
		modelShader->SetMat3f("normal", normal);
		modelShader->SetVec3f("viewPos", camera->GetPosition());
		modelShader->SetVec3f("light.position", lightPos);

		backpack->Draw(*modelShader);

		modelShader->Unuse();

		lightShader->Use();
		lightVa->Bind();

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader->SetMat4f("model", model);
		lightShader->SetMat4f("view", view);
		lightShader->SetMat4f("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightVa->Unbind();
		lightShader->Unuse();
	}
}
