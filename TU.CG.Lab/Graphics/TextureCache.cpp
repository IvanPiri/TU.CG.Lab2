#include "TextureCache.hpp"

#include <filesystem>
#include <iostream>
#include <glad/glad.h>
#include <stb/stb_image.h>

namespace Graphics
{
	TextureCache::TextureCache()
	{
		stbi_set_flip_vertically_on_load(true);
	}

	TextureCache::TextureCache(TextureCache&& other) noexcept
	{
		textureMap.merge(other.textureMap);
	}

	TextureCache& TextureCache::operator=(TextureCache&& other) noexcept
	{
		if (this != &other)
		{
			Clear();

			textureMap.merge(other.textureMap);
		}

		return *this;
	}

	TextureCache::~TextureCache()
	{
		Clear();
	}

	Texture TextureCache::GetTexture(const std::string& filePath)
	{
		const auto umit = textureMap.find(filePath);

		if (umit == textureMap.end())
		{
			auto newTexture = LoadTextureFromFile(filePath);

			textureMap.emplace(filePath, newTexture);

			std::cout <<
				"Loaded texture with file path = { " <<
				filePath <<
				" }" <<
				std::endl;

			return newTexture;
		}

		std::cout <<
			"Used cached texture with file path = { " <<
			filePath <<
			" }" <<
			std::endl;

		return umit->second;
	}

	void TextureCache::DeleteTexture(Texture& texture)
	{
		const auto umit = textureMap.find(texture.filePath);

		if (umit == textureMap.end())
		{
			const std::string errorMessage = "Texture with file path = { " +
				texture.filePath +
				" } was not deleted because it is not a part of this TextureCache.";

			throw std::exception(errorMessage.c_str());
		}

		glDeleteTextures(1, &texture.id);
		textureMap.erase(umit);

		std::cout <<
			"Deleted cached texture with file path = { " <<
			texture.filePath <<
			" }" <<
			std::endl;

		texture.id = 0;
		texture.width = 0;
		texture.height = 0;
		texture.filePath = "";
		texture.fileNameWithoutExtension = "";
	}

	void TextureCache::Clear()
	{
		if (!textureMap.empty())
			std::cout << "Cleared a Texture Cache." << std::endl;

		for (const auto& umit : textureMap)
			glDeleteTextures(1, &umit.second.id);

		textureMap.clear();
	}

	Texture TextureCache::LoadTextureFromFile(const std::string& filePath)
	{
		unsigned textureId;
		int width, height, channels;

		unsigned char* data = stbi_load(
			filePath.c_str(), &width, &height, &channels, 0);

		const std::string fileNameWithoutExtension =
			std::filesystem::path(filePath).stem().string();

		if (data)
		{
			glGenTextures(1, &textureId);
			glBindTexture(GL_TEXTURE_2D, textureId);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			auto format = GL_RGBA;

			if (channels == 1)
				format = GL_RED;
			else if (channels == 3)
				format = GL_RGB;

			glTexImage2D(
				GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);
			stbi_image_free(data);
		}
		else
		{
			stbi_image_free(data);

			const auto errorMessage = "Failed to load texture: " + filePath;
			throw std::exception(errorMessage.c_str());
		}

		return Texture(
			textureId, width, height, filePath, fileNameWithoutExtension);
	}
}
