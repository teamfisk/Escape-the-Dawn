#version 430

uniform mat4 model;
uniform mat4 view;

layout(binding=0) uniform sampler2D texture;

uniform vec3 lightPosition;
uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;

in VertexData {
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoord;
} Input;

out vec4 fragmentColor;

void main() {
	// Texture
	vec4 texel = texture2D(texture, Input.TextureCoord);
	//vec4 texel1 = texture2D(texture1, Input.TextureCoord * 32.0);
	//vec4 texel2 = texture2D(texture2, Input.TextureCoord * 100.0);
	//vec4 blend = texture2D(blendmap, Input.TextureCoord);

	//vec4 texel = (blend.x * texel0) + (blend.y * texel1) + (blend.z * texel2);

	//
	// Phong shading
	//

	// Light
	//vec3 lightPosition = vec3(0, 0, 2);
	vec3 Ls = vec3(1.0, 1.0, 0.9);	// Specular light
	vec3 Ld = vec3(1.0, 1.0, 0.9);	// Diffuse light
	vec3 La = vec3(0.6, 0.6, 0.6);	// Ambient light

	// Object
	vec3 Ks = vec3(0.3, 0.3, 0.3);	// Specular reflectance
	vec3 Kd = vec3(1.0, 1.0, 1.0);	// Diffuse reflectance
	vec3 Ka = vec3(1.0, 1.0, 1.0);	// Ambient reflectance

	vec3 lightPosView = vec3(view * vec4(lightPosition, 1.0));
	vec3 surfacePosition = vec3(model * vec4(Input.Position, 1.0));
	vec3 surfacePosView = vec3(view * vec4(surfacePosition, 1.0));
	vec3 surfaceToLight = normalize(lightPosView - surfacePosView);
	mat3 normalMatrix = transpose(inverse(mat3(view * model)));
	vec3 surfaceNormal = normalize(normalMatrix * Input.Normal);

	// Specular light
	vec3 reflection = reflect(-surfaceToLight, surfaceNormal);
	float dotSpecular = dot(reflection, normalize(-surfacePosView));
	dotSpecular = max(dotSpecular, 0.0);
	float specularFactor = pow(dotSpecular, 30.0); // Specular factor
	vec3 Is = Ls * Ks * specularFactor;

	// Diffuse light
	float dotProd = dot(surfaceToLight, surfaceNormal);
	dotProd = max(dotProd, 0.0);
	vec3 Id = Ld * Kd * abs(dotProd);

	// Ambient light
	vec3 Ia = La * Ka;

	float dist = length(lightPosition - surfacePosition);
	float attenuation = 1.0 / (constantAttenuation
		+ linearAttenuation * dist
		+ quadraticAttenuation * pow(dist, 2.0));

	fragmentColor = vec4((Is + Id) * attenuation + Ia, 1.0) * texel;

	//fragmentColor = vec4(Id, 1.0) * texel;

	//fragmentColor = texel;
}