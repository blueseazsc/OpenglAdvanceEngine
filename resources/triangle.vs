attribute vec4 position;
attribute vec4 texcoord;
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
varying vec4 V_texcoord;

void main() {
	V_texcoord = texcoord;
	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * position;
}
