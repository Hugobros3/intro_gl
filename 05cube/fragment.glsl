#version 330
out vec4 outputColor;
uniform vec4 myColor;

uniform sampler2D textureSampler;
in vec2 texCoordPassed;

void main() {
	outputColor = texture(textureSampler, texCoordPassed);
}