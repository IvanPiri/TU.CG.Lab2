#include "VertexArray.hpp"

#include <glad/glad.h>

namespace Graphics
{
	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &id);
	}

	VertexArray::VertexArray(VertexArray&& other) noexcept
		: id(other.id), vbo(std::move(other.vbo)), ebo(std::move(other.ebo))
	{
		other.id = 0;
	}

	VertexArray& VertexArray::operator=(VertexArray&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			id = other.id;
			vbo = std::move(other.vbo);
			ebo = std::move(other.ebo);

			other.id = 0;
		}

		return* this;
	}

	VertexArray::~VertexArray()
	{
		Delete();
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(id);
	}

	void VertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void VertexArray::SetVertexBuffer(std::unique_ptr<VertexBuffer> vb)
	{
		if (vb == nullptr)
			throw std::exception("Vertex Buffer cannot be null.");

		Bind();

		vbo = std::move(vb);

		vbo->Bind();
		vbo->Configure();
	}

	void VertexArray::SetElementBuffer(std::unique_ptr<ElementBuffer> eb)
	{
		if (eb == nullptr)
			throw std::exception("Element Buffer cannot be null.");

		Bind();

		ebo = std::move(eb);

		ebo->Bind();
	}

	void VertexArray::Delete()
	{
		glDeleteVertexArrays(1, &id);

		vbo = nullptr;
		ebo = nullptr;
	}
}
