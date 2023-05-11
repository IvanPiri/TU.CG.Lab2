#include "Texture.hpp"

#include <glad/glad.h>

namespace Graphics
{
	Texture::Texture(
		const unsigned id, const int width, const int height,
		std::string name, std::string fileNameWithoutExtension)
			: id(id), width(width), height(height), filePath(std::move(name)),
			fileNameWithoutExtension(std::move(fileNameWithoutExtension))
	{
	}

	void Texture::BindAndActivate(const unsigned textureSlot) const
	{
		glActiveTexture(GL_TEXTURE0 + textureSlot);
		glBindTexture(GL_TEXTURE_2D, id);
	}
}
