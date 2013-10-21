#version 130

in vec3 coord;

uniform mat4 mv;

void main() {
  gl_Position = mv * vec4(coord, 1.0);
}
