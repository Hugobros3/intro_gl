#version 330
in vec3 vertexIn;
in vec2 texCoordIn;
uniform vec2 myPosition;
uniform mat4 viewMatrix;

out vec2 texCoordPassed;

void main() {
	//texCoordPassed = vertexIn.xy * 0.5 + vec2(0.5);
	vec4 vertex = vec4(vertexIn, 1.0);
	
	texCoordPassed = texCoordIn;
	texCoordPassed.y = 1.0 - texCoordIn.y;
	
	gl_Position = viewMatrix * vertex;
}
