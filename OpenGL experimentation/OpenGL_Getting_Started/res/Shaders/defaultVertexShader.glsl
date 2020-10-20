#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 transformMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 vsColor;
out vec2 vsTexCoords;

void main()
{
	vsColor = aColor;
	vsTexCoords = aTexCoords;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPosition, 1.0f);
}