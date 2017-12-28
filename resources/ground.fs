#ifdef GL_ES
precision mediump float
#endif 

varying vec4 V_Color;
varying vec3 V_Normal;
varying vec3 V_WorldPos;

void main() {
	gl_FragColor = V_Color;
}
