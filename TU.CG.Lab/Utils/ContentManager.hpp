#pragma once

#include <memory>

#include "Graphics/Model.hpp"
#include "Graphics/ShaderProgram.hpp"
#include "Graphics/Texture.hpp"
#include "Graphics/TextureCache.hpp"

namespace Utils
{
	class ContentManager
	{
		private:
			Graphics::TextureCache textureCache;
		public:
			Graphics::Texture GetTexture(const std::string& filePath);
			void DeleteTexture(Graphics::Texture& texture);

			std::unique_ptr<Graphics::Model> GetModel(const std::string& filePath);

			[[nodiscard]] std::unique_ptr<Graphics::ShaderProgram> GetShader(
				const std::string& vertexShaderPath,
				const std::string& fragmentShaderPath) const;

			void Clear();
	};
}
