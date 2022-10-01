#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTextureCoord;

out vec3 Normal;
out vec3 FragPos; // positon of the vertex in the world's view.
out vec2 TextureCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	FragPos = vec3(model * vec4(aPos, 1.0f));
	gl_Position = proj * view * model * vec4(aPos, 1.0f);
	// See, the next operation is necessary when rotation or scaling operation is performed,
	// because it will change the actual direction of the normal vector, so to undo that we have to do this.
	Normal = mat3(transpose(inverse(model))) * aNormal;
	TextureCoord = aTextureCoord;
}