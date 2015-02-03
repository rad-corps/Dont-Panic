#version 400

smooth in vec4 vertColour;
smooth in vec2 UV;

out vec4 outputColour;
uniform sampler2D textureMap;

void main()
{
	outputColour = texture(textureMap, UV) * vertColour;
	//outputColour = vertColour;
}