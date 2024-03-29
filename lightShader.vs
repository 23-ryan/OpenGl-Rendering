#version 330 core
layout (location = 0) in vec3 aPos;

// out vec3 objectColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

// uniform vec3 sourceColor;

void main()
{
   gl_Position = proj * view * model * vec4(aPos, 1.0f);
   // objectColor = sourceColor;
}
