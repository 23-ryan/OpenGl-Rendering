#version 330 core
layout (location = 2) in vec3 aPos;
layout (location = 3) in vec2 aTexCoord;

out vec2 TexCoord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
   gl_Position = proj * view * model * vec4(aPos, 1.0f);
   //gl_Position = vec4(aPos, 1.0f);
   TexCoord = aTexCoord;
}