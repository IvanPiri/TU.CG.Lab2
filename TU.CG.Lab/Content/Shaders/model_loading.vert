#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal;

out vec2 TexCoords;
out vec3 FragPos;
out vec3 Normal;

void main()
{
	vec4 position = vec4(aPos, 1.0f);

	gl_Position = projection * view * model * position;

	FragPos = vec3(model * position);
	Normal = normal * aNormal;
	TexCoords = aTexCoords;
}
