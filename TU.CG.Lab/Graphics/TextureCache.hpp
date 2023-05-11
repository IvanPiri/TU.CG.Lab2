#pragma once

#include <string>
#include <unordered_map>

#include "Texture.hpp"

namespace Graphics
{
	class TextureCache
	{
		private:
			std::unordered_map<std::string, Texture> textureMap;

			static Texture LoadTextureFromFile(const std::string& filePath);
		public:
			TextureCache();
			TextureCache(const TextureCache& other) = delete;
			TextureCache& operator=(const TextureCache& other) = delete;
			TextureCache(TextureCache&& other) noexcept;
			TextureCache& operator=(TextureCache&& other) noexcept;
			~TextureCache();

			Texture GetTexture(const std::string& filePath);
			void DeleteTexture(Texture& texture);

			void Clear();
	};
}
