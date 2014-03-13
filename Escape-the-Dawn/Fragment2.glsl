uniform mat4 model;
uniform mat4 view;
 
layout(binding=0) uniform sampler2D texture;

const int numberOfLights = 2;
lightSource lights[numberOfLights];

uniform vec4 position[numberOfLights];
uniform vec4 specular[numberOfLights];
uniform vec4 diffuse[numberOfLights];
uniform float constantAttenuation[numberOfLights];
uniform float linearAttenuation[numberOfLights];
uniform float quadraticAttenuation[numberOfLights];
uniform float spotExponent[numberOfLights];

 in VertexData {
	vec3 Position;
	vec3 Normal;
	vec2 TextureCoord;
} Input;

vec4 scene_ambient = vec4(0.2, 0.2, 0.2, 1.0);
 
out vec4 fragmentColor;

void main()
{
  
  vec4 texel = texture2D(texture, Input.TextureCoord);

  vec3 normalDirection = normalize(Normal);
  vec3 viewDirection = normalize(vec3(v_inv * vec4(0.0, 0.0, 0.0, 1.0) - Position));
  vec3 lightDirection;
  float attenuation;
 
  // initialize total lighting with ambient lighting
  vec3 totalLighting = vec3(scene_ambient) * vec3(frontMaterial.ambient);
 
  for (int index = 0; index < numberOfLights; index++) // for all light sources
    {
	vec3 positionToLightSource = vec3(position[index] - Position);
	float distance = length(positionToLightSource);
	lightDirection = normalize(positionToLightSource);

	attenuation = 1.0 / (constantAttenuation[index]
			       + linearAttenuation[index] * distance
			       + quadraticAttenuation[index] * distance * distance);
 
	attenuation = attenuation * pow(clampedCosine, spotExponent[index]);   
 
      vec3 diffuseReflection = attenuation 
	* vec3(diffuse[index]) * vec3(frontMaterial.diffuse)
	* max(0.0, dot(normalDirection, lightDirection));
 
      vec3 specularReflection;
      if (dot(normalDirection, lightDirection) < 0.0) // light source on the wrong side?
	{
	  specularReflection = vec3(0.0, 0.0, 0.0); // no specular reflection
	}
      else // light source on the right side
	{
	  specularReflection = attenuation * vec3(specular[index]) * vec3(frontMaterial.specular) 
	    * pow(max(0.0, dot(reflect(-lightDirection, normalDirection), viewDirection)), frontMaterial.shininess);
	}
 
      totalLighting = totalLighting + diffuseReflection + specularReflection;
    }
 
  fragmentColor = vec4(totalLighting, 1.0) * texel;
}