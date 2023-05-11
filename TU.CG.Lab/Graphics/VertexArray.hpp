#pragma once

#include <memory>

#include "ElementBuffer.hpp"
#include "VertexBuffer.hpp"

namespace Graphics
{
	class VertexArray
	{
		private:
			unsigned id = 0;

			std::unique_ptr<VertexBuffer> vbo;
			std::unique_ptr<ElementBuffer> ebo;

			void Delete();
		public:
			VertexArray();
			VertexArray(const VertexArray& other) = delete;
			VertexArray& operator=(const VertexArray& other) = delete;
			VertexArray(VertexArray&& other) noexcept;
			VertexArray& operator=(VertexArray&& other) noexcept;
			~VertexArray();

			void Bind() const;
			void Unbind();

			void SetVertexBuffer(std::unique_ptr<VertexBuffer> vb);
			void SetElementBuffer(std::unique_ptr<ElementBuffer> eb);

			[[nodiscard]] ElementBuffer* GetEbo() const { return ebo.get(); }
	};
}
