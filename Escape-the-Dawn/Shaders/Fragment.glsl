#version 440

uniform mat4 MVP;
uniform sampler2D texture0;

in VertexData {
	vec3 Position;
	vec3 Color;
	vec2 TextureCoord;
} Input;

out vec4 FragmentColor;

void main()
{
	vec4 texel = texture2D(texture0, Input.TextureCoord);
	FragmentColor = texel * vec4(Input.Color, 0);
}