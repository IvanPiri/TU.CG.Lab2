#pragma once

#include <string>

namespace Graphics
{
	class Texture
	{
		private:
			unsigned id;
			int width;
			int height;

			std::string filePath;
			std::string fileNameWithoutExtension;

			friend class TextureCache;
		public:
			Texture(
				unsigned id, int width, int height,
				std::string name, std::string fileNameWithoutExtension);

			void BindAndActivate(unsigned textureSlot = 0) const;

			[[nodiscard]] int GetWidth() const { return width; }
			[[nodiscard]] int GetHeight() const { return height; }
			[[nodiscard]] std::string GetFilePath() const { return  filePath; }
			[[nodiscard]] std::string GetFileNameWithoutExtension() const { return fileNameWithoutExtension; }
	};
}
