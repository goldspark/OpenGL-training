#version 330

layout (location = 0) in vec3 pos;

out vec4 Color;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main(){

  gl_Position = vec4(pos, 1.0);
  Color = vec4(clamp(pos, 0.0f, 1.0f), 1.0);
}