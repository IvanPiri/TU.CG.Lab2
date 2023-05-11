#include "Application_Lighting.hpp"

#include <glad/glad.h>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb/stb_image.h>

namespace Applications
{
	Application_Lighting::Application_Lighting()
		: lightPos(1.2f, 1.0f, 2.0f)
	{
		window = std::make_unique<Utils::Window>("TU.CG.Lab", 800, 600);
	}

	void Application_Lighting::Run()
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

	void Application_Lighting::Initialize()
	{
		window->ActivateInputFor(this);

		camera = std::make_unique<Utils::Camera3D>(
			glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), 45.0f);

		stbi_set_flip_vertically_on_load(true);

		glEnable(GL_DEPTH_TEST);
	}

	void Application_Lighting::LoadContent()
	{
		//
		// -- Textures
		//

		boxDiffuseMap = std::make_unique<Graphics::Texture>(
			content.GetTexture("Content/Textures/container2.png"));

		boxSpecularMap = std::make_unique<Graphics::Texture>(
			content.GetTexture("Content/Textures/container2_specular.png"));

		//
		// --- Buffers
		//

		constexpr float lightVertices[] =
		{
			// positions
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

		constexpr float vertices[] =
		{
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		};

		lightVa = std::make_unique<Graphics::VertexArray>();

		auto lightVb = std::make_unique<Graphics::VertexBuffer>(
			lightVertices, sizeof lightVertices);

		lightVb->SetAttributes({
			{"aPos", Graphics::VertexAttributeType::VEC3F},
		});

		lightVa->SetVertexBuffer(std::move(lightVb));

		objectVa = std::make_unique<Graphics::VertexArray>();

		auto objectVb = std::make_unique<Graphics::VertexBuffer>(
			vertices, sizeof vertices);

		objectVb->SetAttributes({
			{"aPos", Graphics::VertexAttributeType::VEC3F},
			{"aNormal", Graphics::VertexAttributeType::VEC3F},
			{"aTexCoords", Graphics::VertexAttributeType::VEC2F},
		});

		objectVa->SetVertexBuffer(std::move(objectVb));

		//
		// --- Shaders
		//

		lightShader = content.GetShader(
			"Content/Shaders/light_box.vert",
			"Content/Shaders/light_box.frag");

		objectShader = content.GetShader(
			"Content/Shaders/lighting.vert",
			"Content/Shaders/lighting.frag");

		objectShader->Use();

		objectShader->SetInt("material.diffuse", 0);
		objectShader->SetInt("material.specular", 1);
		objectShader->SetFloat("material.shininess", 128.0f);
		objectShader->SetVec3f("light.position", lightPos);
		objectShader->SetVec3f("light.ambient", glm::vec3(0.2f));
		objectShader->SetVec3f("light.diffuse", glm::vec3(0.5f));
		objectShader->SetVec3f("light.specular", glm::vec3(1.0f));

		objectShader->Unuse();
	}

	void Application_Lighting::UnloadContent()
	{
		content.Clear();

		objectVa = nullptr;
		objectShader = nullptr;
		lightVa = nullptr;
		lightShader = nullptr;
	}

	void Application_Lighting::Update(const float deltaTime)
	{
		if (inputManager.IsKeyDown(Input::Keys::ESCAPE))
			window->SetShouldClose(true);

		camera->Update(deltaTime, inputManager);

		inputManager.ResetState();
	}

	void Application_Lighting::Render() const
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		auto model = glm::mat4(1.0f);

		const auto view = camera->GetViewMatrix();

		const auto windowSize = window->GetSize();

		const auto projection = glm::perspective(
			glm::radians(camera->GetZoom()), windowSize.x / windowSize.y, 0.1f, 100.0f);

		const auto normalMatrix = glm::inverseTranspose(glm::mat3(model));

		objectShader->Use();
		objectVa->Bind();

		boxDiffuseMap->BindAndActivate(0);
		boxSpecularMap->BindAndActivate(1);

		objectShader->SetMat4f("model", model);
		objectShader->SetMat4f("view", view);
		objectShader->SetMat4f("projection", projection);
		objectShader->SetMat3f("normal", normalMatrix);
		objectShader->SetVec3f("viewPos", camera->GetPosition());

		glDrawArrays(GL_TRIANGLES, 0, 36);

		objectVa->Unbind();
		objectShader->Unuse();

		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));

		lightShader->Use();
		lightVa->Bind();

		lightShader->SetMat4f("model", model);
		lightShader->SetMat4f("view", view);
		lightShader->SetMat4f("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightVa->Unbind();
		lightShader->Unuse();
	}
}
