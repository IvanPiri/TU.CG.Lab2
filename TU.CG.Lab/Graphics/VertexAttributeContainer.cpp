#include "VertexAttributeContainer.hpp"

#include <glad/glad.h>

namespace Graphics
{
	VertexAttribute::VertexAttribute(std::string name, const VertexAttributeType type)
		: name(std::move(name)), type(type), size(GetSizeOfType(type)), offset(0)
	{
	}

	VertexAttributeContainer::VertexAttributeContainer(
		const std::initializer_list<VertexAttribute> attributes)
			: attributes(attributes)
	{
		unsigned offset = 0;

		for (auto& attribute : this->attributes)
		{
			attribute.offset = offset;
			offset += attribute.size;
			stride += attribute.size;
		}
	}

	size_t GetSizeOfType(const VertexAttributeType type)
	{
		switch (type)
		{
			case VertexAttributeType::FLOAT:
			case VertexAttributeType::VEC2F:
			case VertexAttributeType::VEC3F:
			case VertexAttributeType::VEC4F:
			case VertexAttributeType::MAT3F:
			case VertexAttributeType::MAT4F:
				return GetCompontentCount(type) * sizeof(float);
		}

		const std::string errorMessage = "Unhandled Vertex attribute type " +
			std::to_string(static_cast<int>(type));

		throw std::exception(errorMessage.c_str());
	}

	int GetCompontentCount(const VertexAttributeType type)
	{
		switch (type)
		{
			case VertexAttributeType::FLOAT:
				return 1;
			case VertexAttributeType::VEC2F:
				return 2;
			case VertexAttributeType::VEC3F:
				return 3;
			case VertexAttributeType::VEC4F:
				return 4;
			case VertexAttributeType::MAT3F:
				return 9;
			case VertexAttributeType::MAT4F:
				return 16;
		}

		const std::string errorMessage = "Unhandled Vertex attribute type " +
			std::to_string(static_cast<int>(type));

		throw std::exception(errorMessage.c_str());
	}

	int GetComponentGLType(const VertexAttributeType type)
	{
		switch (type)
		{
			case VertexAttributeType::FLOAT:
			case VertexAttributeType::VEC2F:
			case VertexAttributeType::VEC3F:
			case VertexAttributeType::VEC4F:
			case VertexAttributeType::MAT3F:
			case VertexAttributeType::MAT4F:
				return GL_FLOAT;
		}

		const std::string errorMessage = "Unhandled Vertex attribute type " +
			std::to_string(static_cast<int>(type));

		throw std::exception(errorMessage.c_str());
	}
}
