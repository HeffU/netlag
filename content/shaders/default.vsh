#version 330

layout(location=0) in vec3 vp;
layout(location=1) in vec3 pos;

void main() {
	gl_Position = vec4(vp + pos, 1.0);
}