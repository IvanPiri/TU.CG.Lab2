#include "Mesh.hpp"

#include <glad/glad.h>

namespace Graphics
{
	Mesh::Mesh(
		const std::vector<Vertex>& vertices,
		const std::vector<unsigned>& indices,
		std::vector<Texture> textures)
			: textures(std::move(textures))
	{
		if (vertices.empty())
			throw std::exception("Vertices array cannot be empty.");

		if (indices.empty())
			throw std::exception("Indices array cannot be empty.");

		va = std::make_unique<VertexArray>();
		va->Bind();

		auto vb = std::make_unique<VertexBuffer>(
			vertices.data(), vertices.size() * sizeof(Vertex));

		vb->Bind();

		vb->SetAttributes({
			{"aPos", VertexAttributeType::VEC3F},
			{"aNormal", VertexAttributeType::VEC3F},
			{"aTexCoords", VertexAttributeType::VEC2F},
		});

		auto eb = std::make_unique<ElementBuffer>(
			indices.data(), indices.size());

		eb->Bind();

		va->SetVertexBuffer(std::move(vb));
		va->SetElementBuffer(std::move(eb));
	}

	Mesh::Mesh(Mesh&& other) noexcept
		: va(std::move(other.va)), textures(std::move(other.textures))
	{
	}

	Mesh& Mesh::operator=(Mesh&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			va = std::move(other.va);
			textures = std::move(other.textures);
		}

		return *this;
	}

	Mesh::~Mesh()
	{
		Delete();
	}

	void Mesh::Draw(const ShaderProgram& shader) const
	{
		for (unsigned i = 0; i < textures.size(); ++i)
		{
			shader.SetInt(
				"material." + textures[i].GetFileNameWithoutExtension(),
				i);

			textures[i].BindAndActivate(i);
		}

		va->Bind();

		glDrawElements(
			GL_TRIANGLES, va->GetEbo()->GetCount(),
			GL_UNSIGNED_INT, nullptr);

		va->Unbind();
	}

	void Mesh::Delete()
	{
		textures.clear();
		va = nullptr;
	}
}
