#version 330 core

in vec3 vsColor;
in vec2 vsTexCoords;

out vec4 fragColor;

uniform sampler2D textureSampler;
uniform sampler2D textureSampler2;

void main()
{
	fragColor = mix(texture(textureSampler, vsTexCoords), texture(textureSampler2, vsTexCoords), 0.5f);
}