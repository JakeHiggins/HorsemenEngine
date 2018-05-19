#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

in vec3 LightDirection_tangentspace;
in vec3 EyeDirection_tangentspace;

out vec4 color;

uniform sampler2D DiffuseTextureSampler;
uniform sampler2D NormalTextureSampler;
uniform mat4 V;
uniform mat4 M;
uniform mat4 MV;
uniform vec3 LightPosition_worldspace;

void main() {
	vec4 LightColor = vec4(1, 1, 1, 1);
	float LightPower = 50.0f;

	vec4 MaterialDiffuseColor = texture(DiffuseTextureSampler, UV).rgba;
	vec4 MaterialAmbientColor = vec4(0.1, 0.1, 0.1, 1) * MaterialDiffuseColor;
	vec4 MaterialSpecularColor = vec4(0.3, 0.3, 0.3, 1);

	vec3 TextureNormal_tangentspace = normalize(texture(NormalTextureSampler, vec2(UV.x, -UV.y)).rgb * 2.0 - 1.0);

	float distance = length(LightPosition_worldspace - Position_worldspace);

	vec3 n = TextureNormal_tangentspace;
	vec3 l = normalize(LightDirection_tangentspace);
	
	float cosTheta = clamp(dot(n, l), 0, 1);

	vec3 E = normalize(EyeDirection_tangentspace);
	vec3 R = reflect(-l, n);

	float cosAlpha = clamp(dot(E, R), 0, 1);

	color = 
		MaterialAmbientColor + 
		MaterialDiffuseColor * LightColor * LightPower * cosTheta / (distance * distance) + 
		MaterialSpecularColor * LightColor * LightPower * pow(cosAlpha, 5) / (distance * distance);
}