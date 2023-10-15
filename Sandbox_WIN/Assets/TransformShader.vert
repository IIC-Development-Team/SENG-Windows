#version 410 core
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;


uniform mat4 MVP;
out vec3 vColor;
out vec2 vUV;

void main(){

	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
	vColor = color;
	vUV = uv;
}
