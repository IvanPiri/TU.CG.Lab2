#version 330 core

in vec2 texCoord;

uniform sampler2D boxTexture;
uniform sampler2D faceTexture;

out vec4 FragColor;

void main()
{
	FragColor = mix(
		texture(boxTexture, texCoord),
		texture(faceTexture, texCoord), 0.2f);
}
