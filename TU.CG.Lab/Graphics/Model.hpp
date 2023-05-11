#pragma once

#include <vector>

#include "Mesh.hpp"
#include "ShaderProgram.hpp"

namespace Graphics
{
	class Model
	{
		private:
			std::vector<Mesh> meshes;

			void Delete();
		public:
			explicit Model(std::vector<Mesh> meshes);
			Model(const Model& other) = delete;
			Model& operator=(const Model& other) = delete;
			Model(Model&& other) noexcept;
			Model& operator=(Model&& other) noexcept;
			~Model();

			void Draw(const ShaderProgram& shader) const;
	};
}
