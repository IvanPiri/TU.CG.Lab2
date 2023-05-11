#pragma once

#include "VertexAttributeContainer.hpp"

namespace Graphics
{
	class VertexBuffer
	{
		private:
			unsigned id = 0;
			VertexAttributeContainer attributes;

			void Delete() const;
		public:
			VertexBuffer(const void* data, size_t size);
			VertexBuffer(const VertexBuffer& other) = delete;
			VertexBuffer& operator=(const VertexBuffer& other) = delete;
			VertexBuffer(VertexBuffer&& other) noexcept;
			VertexBuffer& operator=(VertexBuffer&& other) noexcept;
			~VertexBuffer();

			void Bind() const;
			void Unbind();
			void Configure();

			void SetAttributes(const VertexAttributeContainer& newAttributes)
			{
				attributes = newAttributes;
			}
	};
}
