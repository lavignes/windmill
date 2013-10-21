#version 130

out vec4 color;
uniform vec3 f_color;

void main() {
  color = vec4(f_color, 1.0);
}
