#include "ContentManager.hpp"

#include "Graphics/ModelLoader.hpp"

namespace Utils
{
	Graphics::Texture ContentManager::GetTexture(const std::string& filePath)
	{
		return textureCache.GetTexture(filePath);
	}

	void ContentManager::DeleteTexture(Graphics::Texture& texture)
	{
		textureCache.DeleteTexture(texture);
	}

	std::unique_ptr<Graphics::Model> ContentManager::GetModel(const std::string& filePath)
	{
		return Graphics::ModelLoader::Load(filePath, textureCache);
	}

	std::unique_ptr<Graphics::ShaderProgram> ContentManager::GetShader(
		const std::string& vertexShaderPath,
		const std::string& fragmentShaderPath) const
	{
		// TODO: Possible optimization: shader cache

		return std::make_unique<Graphics::ShaderProgram>(
			vertexShaderPath, fragmentShaderPath);
	}

	void ContentManager::Clear()
	{
		textureCache.Clear();
	}
}
