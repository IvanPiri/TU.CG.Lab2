#pragma once

#include <string>
#include <vector>

namespace Graphics
{
	enum class VertexAttributeType
	{
		FLOAT,
		VEC2F,
		VEC3F,
		VEC4F,
		MAT3F,
		MAT4F,
	};

	struct VertexAttribute
	{
		std::string name;
		VertexAttributeType type;
		size_t size;
		unsigned offset;

		VertexAttribute(std::string name, VertexAttributeType type);
	};

	class VertexAttributeContainer
	{
		private:
			std::vector<VertexAttribute> attributes;
			size_t stride = 0;
		public:
			using iterator = std::vector<VertexAttribute>::iterator;
			using const_iterator = std::vector<VertexAttribute>::const_iterator;

			VertexAttributeContainer() = default;
			VertexAttributeContainer(std::initializer_list<VertexAttribute> attributes);

			iterator begin() { return attributes.begin(); }
			iterator end() { return attributes.end(); }

			[[nodiscard]] const_iterator begin() const { return attributes.begin(); }
			[[nodiscard]] const_iterator end() const { return attributes.end(); }

			[[nodiscard]] size_t GetStride() const { return stride; }
	};

	extern size_t GetSizeOfType(VertexAttributeType type);
	extern int GetCompontentCount(VertexAttributeType type);
	extern int GetComponentGLType(VertexAttributeType type);
}
