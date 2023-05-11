#include "Model.hpp"

namespace Graphics
{
	Model::Model(std::vector<Mesh> meshes)
		: meshes(std::move(meshes))
	{
		if (this->meshes.empty())
			throw std::exception("Meshes array cannot be empty.");
	}

	Model::Model(Model&& other) noexcept
		: meshes(std::move(other.meshes))
	{
	}

	Model& Model::operator=(Model&& other) noexcept
	{
		if (this != &other)
		{
			Delete();

			meshes = std::move(other.meshes);
		}

		return *this;
	}

	Model::~Model()
	{
		Delete();
	}

	void Model::Draw(const ShaderProgram& shader) const
	{
		for (const auto& mesh : meshes)
			mesh.Draw(shader);
	}

	void Model::Delete()
	{
		meshes.clear();
	}
}
