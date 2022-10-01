#version 330 core

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TextureCoord;

uniform vec3 lightPos;
uniform vec3 viewPos;

struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform Material material;
uniform Light light;

void main(){
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 norm = normalize(Normal);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = (diff * light.diffuse) * vec3(texture(material.diffuse, TextureCoord));

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TextureCoord));

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(reflectDir, viewDir), 0.0f), material.shininess); // material.shininess--> represents the shininess.
	vec3 specular = (spec * light.specular) * (vec3(texture(material.specular, TextureCoord)));

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0f);
}