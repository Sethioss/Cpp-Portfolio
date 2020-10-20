#version 330 core

layout (location = 0) in vec3 aPosition;
layout  (location = 1) in vec3 aNormal;

out vec3 FragmentPos;
out vec3 Normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	FragmentPos = vec3(modelMatrix * vec4(aPosition, 1.0));
	Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;

	gl_Position = projectionMatrix * viewMatrix * vec4(FragmentPos, 1.0);
}