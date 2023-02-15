#version 330 core
in vec3 normal;
in vec3 fragPos;

uniform vec3 u_lightPos;
uniform vec3 u_viewPos;

out vec4 out_color;

void main()
{
	float ambientStr = 0.1;
	float specularStr = 0.5;
	vec3 lightColor = vec3(10.0, 10.0, 10.0);
	vec3 objColor = vec3(1.0, 0.66, 0.46);

	vec3 ambient = ambientStr * lightColor;

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(u_lightPos - fragPos);
	vec3 diffuse = max(dot(norm, lightDir), 0.0) * lightColor;
	
	vec3 viewDir = normalize(u_viewPos - fragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	vec3 spec = specularStr * pow(max(dot(viewDir, reflectDir), 0.0), 32) * lightColor;

	out_color = vec4((ambient + diffuse + spec) * objColor, 1.0);
}