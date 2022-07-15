#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture1;

void main(){
	FragColor = mix(texture(ourTexture1, vec2(TexCoord.x, TexCoord.y)), texture(ourTexture, TexCoord), 0.7f);
}