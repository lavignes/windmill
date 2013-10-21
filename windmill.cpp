#include <GL/glew.h>

#include "windmill.h"

const vec3 Windmill::BLUE(0.0f, 0.0f, 1.0f);
const vec3 Windmill::RED(1.0f, 0.0f, 0.0f);
const vec3 Windmill::GREEN(0.0f, 1.0f, 0.0f);
const vec3 Windmill::CYAN(0.0f, 1.0f, 1.0f);
const vec3 Windmill::MAGENTA(1.0f, 0.0f, 1.0f);
const vec3 Windmill::YELLOW(1.0f, 1.0f, 0.0f);

const mat4 Windmill::scale_post = mat4::scale(8.0f, 80.0f, 8.0f);
const mat4 Windmill::scale_blade = mat4::scale(12.0f, 40.0f, 4.0f);

// 0.01 lengthed unit cube
const vec3 Windmill::cube[36] = {
  vec3(-0.005f, 0.005f, 0.005f),
  vec3(-0.005f, -0.005f, 0.005f),
  vec3(0.005f, 0.005f, 0.005f),
  vec3(0.005f, 0.005f, 0.005f),
  vec3(-0.005f, -0.005f, 0.005f),
  vec3(0.005f, -0.005f, 0.005f),

  vec3(0.005f, 0.005f, 0.005f),
  vec3(0.005f, -0.005f, 0.005f),
  vec3(0.005f, 0.005f, -0.005f),
  vec3(0.005f, 0.005f, -0.005f),
  vec3(0.005f, -0.005f, 0.005f),
  vec3(0.005f, -0.005f, -0.005f),

  vec3(0.005f, 0.005f, -0.005f),
  vec3(0.005f, -0.005f, -0.005f),
  vec3(-0.005f, 0.005f, -0.005f),
  vec3(-0.005f, 0.005f, -0.005f),
  vec3(0.005f, -0.005f, -0.005f),
  vec3(-0.005f, -0.005f, -0.005f),

  vec3(-0.005f, 0.005f, -0.005f),
  vec3(-0.005f, -0.005f, -0.005f),
  vec3(-0.005f, 0.005f, 0.005f),
  vec3(-0.005f, 0.005f, 0.005f),
  vec3(-0.005f, -0.005f, -0.005f),
  vec3(-0.005f, -0.005f, 0.005f),

  vec3(-0.005f, 0.005f, -0.005f),
  vec3(-0.005f, 0.005f, 0.005f),
  vec3(0.005f, 0.005f, -0.005f),
  vec3(0.005f, 0.005f, -0.005f),
  vec3(-0.005f, 0.005f, 0.005f),
  vec3(0.005f, 0.005f, 0.005f),

  vec3(-0.005f, -0.005f, 0.005f),
  vec3(-0.005f, -0.005f, -0.005f),
  vec3(0.005f, -0.005f, 0.005f),
  vec3(0.005f, -0.005f, 0.005f),
  vec3(-0.005f, -0.005f, -0.005f),
  vec3(0.005f, -0.005f, -0.005f)
};

Windmill::Windmill(Pipeline* program) {
  this->program = program;

  // Send points to gfx card
  glGenBuffers(1, &cube_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, cube_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(cube), cube, GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glUseProgram(program->get_id());
  program->bind_attribute("coord", 0);
  glEnableVertexAttribArray(program->get_attribute(0));
  glVertexAttribPointer(
    program->get_attribute(0), 3, GL_FLOAT, false, 0, (void*)(0));

  program->bind_uniform("mv", 0);
  program->bind_uniform("f_color", 1);

  angle_blades = 0.0f;

  angle_x_post = 0.0f;
  angle_y_post = 0.0f;
  angle_z_post = 0.0f;
}

Windmill::~Windmill() {
  glDeleteBuffers(1, &cube_vbo);
  glDeleteVertexArrays(1, &vao);
}

void Windmill::draw() {

  glBindVertexArray(vao);
  
  rot = mat4::rotate_x(angle_x_post)
      * mat4::rotate_y(angle_y_post)
      * mat4::rotate_z(angle_z_post);

  // Draw post
  mat4 mv = scale_post * rot;
  glUniformMatrix4fv(program->get_uniform(0), 1, false, mv.as_array());
  glUniform3fv(program->get_uniform(1), 1, RED.as_array());
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Draw top (GREEN) blade
  mv = scale_blade * mat4::translate(0.0f, 0.26f, -0.06f).transpose()
     * mat4::rotate_z(angle_blades)
     * mat4::translate(0.0f, 0.4f, 0.0f).transpose() * rot;
  glUniformMatrix4fv(program->get_uniform(0), 1, false, mv.as_array());
  glUniform3fv(program->get_uniform(1), 1, GREEN.as_array());
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Draw right (YELLOW) blade
  mv = scale_blade * mat4::translate(0.0f, 0.26f, -0.06f).transpose()
     * mat4::rotate_z(angle_blades+90.0f)
     * mat4::translate(0.0f, 0.4f, 0.0f).transpose() * rot;
  glUniformMatrix4fv(program->get_uniform(0), 1, false, mv.as_array());
  glUniform3fv(program->get_uniform(1), 1, YELLOW.as_array());
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Draw bottm (CYAN) blade
  mv = scale_blade * mat4::translate(0.0f, 0.26f, -0.06f).transpose()
     * mat4::rotate_z(angle_blades+180.0f)
     * mat4::translate(0.0f, 0.4f, 0.0f).transpose() * rot;
  glUniformMatrix4fv(program->get_uniform(0), 1, false, mv.as_array());
  glUniform3fv(program->get_uniform(1), 1, CYAN.as_array());
  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Draw left (BLUE) blade
  mv = scale_blade * mat4::translate(0.0f, 0.26f, -0.06f).transpose()
     * mat4::rotate_z(angle_blades+270.0f)
     * mat4::translate(0.0f, 0.4f, 0.0f).transpose() * rot;
  glUniformMatrix4fv(program->get_uniform(0), 1, false, mv.as_array());
  glUniform3fv(program->get_uniform(1), 1, BLUE.as_array());
  glDrawArrays(GL_TRIANGLES, 0, 36);
}

float Windmill::get_blade_angle() const {
  return angle_blades;
}

void Windmill::set_blade_angle(float angle) {
  angle_blades = angle;
}

float Windmill::get_angle_x() const {
  return angle_x_post;
}

void Windmill::set_angle_x(float angle) {
  angle_x_post = angle;
}

float Windmill::get_angle_y() const {
  return angle_y_post;
}

void Windmill::set_angle_y(float angle) {
  angle_y_post = angle;
}

float Windmill::get_angle_z() const {
  return angle_z_post;
}

void Windmill::set_angle_z(float angle) {
  angle_z_post = angle;
}