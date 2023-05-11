#include "ElementBuffer.hpp"

#include <glad/glad.h>

namespace Graphics
{
	ElementBuffer::ElementBuffer(const unsigned* data, const int count)
		: count(count)
	{
		glGenBuffers(1, &id);

		Bind();

		glBufferData(
			GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data, GL_STATIC_DRAW);

		Unbind();
	}

	ElementBuffer::ElementBuffer(ElementBuffer&& other) noexcept
		: id(other.id), count(other.count)
	{
		other.id = 0;
		other.count = 0;
	}

	ElementBuffer& ElementBuffer::operator=(ElementBuffer&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			id = other.id;
			count = other.count;

			other.id = 0;
			other.count = 0;
		}

		return *this;
	}

	ElementBuffer::~ElementBuffer()
	{
		Delete();
	}

	void ElementBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void ElementBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void ElementBuffer::Delete() const
	{
		glDeleteBuffers(1, &id);
	}
}
