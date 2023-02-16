#version 330 core
in vec3 normal;
in vec3 fragPos;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;
uniform vec3 u_lightCol;
uniform vec3 u_objectCol;

out vec4 out_color;

void main()
{
	float ambientStr = 0.1;
	float specularStr = 0.5;

	vec3 ambient = ambientStr * u_lightCol;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(u_lightPos - fragPos);
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * u_lightCol;
	
	vec3 viewDir = normalize(u_viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 specular = specularStr * pow(max(dot(viewDir, reflectDir), 0.0), 32) * u_lightCol;

	out_color = vec4((ambient + diffuse + specular) * u_objectCol, 1.0);
}