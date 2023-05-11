#pragma once

#include <memory>
#include <vector>
#include <glm/glm.hpp>

#include "ShaderProgram.hpp"
#include "Texture.hpp"
#include "VertexArray.hpp"

namespace Graphics
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class Mesh
	{
		private:
			std::unique_ptr<VertexArray> va;

			void Delete();
		public:
			std::vector<Texture> textures;

			Mesh(
				const std::vector<Vertex>& vertices,
				const std::vector<unsigned>& indices,
				std::vector<Texture> textures);

			Mesh(const Mesh& other) = delete;
			Mesh& operator=(const Mesh& other) = delete;
			Mesh(Mesh&& other) noexcept;
			Mesh& operator=(Mesh&& other) noexcept;
			~Mesh();

			void Draw(const ShaderProgram& shader) const;
	};
}
