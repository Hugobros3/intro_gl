#version 330
in vec2 vertexIn;
uniform vec2 myPosition;

out vec2 texCoordPassed;

void main() {
	texCoordPassed = vertexIn * 0.5 + vec2(0.5);
	texCoordPassed.y = 1.0 - texCoordPassed.y;
	
	gl_Position = vec4(vertexIn * 0.5 + myPosition, 0.0f, 1.0f);
}
