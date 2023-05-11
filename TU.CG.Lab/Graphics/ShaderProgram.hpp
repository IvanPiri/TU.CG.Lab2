#pragma once

#include <glm/glm.hpp>
#include <string>

namespace Graphics
{
	class ShaderProgram
	{
		private:
			unsigned id = 0;

			static void DeleteShaders(unsigned vertexShaderId, unsigned fragmentShaderId);

			static std::string ReadShaderFile(const std::string& shaderPath);

			static bool CompileShader(
				unsigned shaderId, const std::string& code, std::string& errorMessage);

			bool LinkProgram(
				unsigned vertexShaderId, unsigned fragmentShaderId, std::string& errorMessage);

			[[nodiscard]] int GetUniformLocation(const std::string& name) const;

			void Delete() const;
		public:
			ShaderProgram(
				const std::string& vertexShaderPath,
				const std::string& fragmentShaderPath);

			ShaderProgram(const ShaderProgram& other) = delete;
			ShaderProgram& operator=(const ShaderProgram& other) = delete;

			ShaderProgram(ShaderProgram&& other) noexcept;
			ShaderProgram& operator=(ShaderProgram&& other) noexcept;

			~ShaderProgram();

			void Use() const;
			void Unuse();

			void SetBool(const std::string& name, bool value) const;
			void SetInt(const std::string& name, int value) const;
			void SetFloat(const std::string& name, float value) const;
			void SetVec2f(const std::string& name, const glm::vec2& value) const;
			void SetVec3f(const std::string& name, const glm::vec3& value) const;
			void SetVec4f(const std::string& name, const glm::vec4& value) const;
			void SetMat3f(const std::string& name, const glm::mat3& value) const;
			void SetMat4f(const std::string& name, const glm::mat4& value) const;
	};
}
