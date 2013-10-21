#include "game.h"
#include "shader.h"
#include "windmill.h"

void step(void* data) {
  static bool turn = false;
  Windmill* windmill = (Windmill*) data;

  if (Game::is_key_pressed('q'))
    Game::quit();

  if (Game::is_key_held('x')) {
    windmill->set_angle_x(windmill->get_angle_x() + 5.0f);
  }

  if (Game::is_key_held('y')) {
    windmill->set_angle_y(windmill->get_angle_y() + 5.0f);
  }

  if (Game::is_key_held('z')) {
    windmill->set_angle_z(windmill->get_angle_z() + 5.0f);
  }

  if (Game::is_key_pressed('r')) {
    turn = false;
    windmill->set_blade_angle(0.0f);
    windmill->set_angle_x(0.0f);
    windmill->set_angle_y(0.0f);
    windmill->set_angle_z(0.0f);
  }

  if (Game::is_key_pressed('s')) {
    turn = !turn;
  }

  if (turn) {
    windmill->set_blade_angle(windmill->get_blade_angle() + 5.0f);
  }
}

int main(int argc, char** argv) {
  Game::init(&argc, argv, "Windmill Thing");

  Pipeline* program = new Pipeline(
    new Pipeline::Shader(Pipeline::Shader::VERTEX, "model.vert"),
    new Pipeline::Shader(Pipeline::Shader::FRAGMENT, "model.frag"));

  Windmill* windmill = new Windmill(program);

  Game::add_model(windmill);
  Game::set_step_callback(step, windmill);
  Game::run();

  delete windmill;
  delete program;
  return 0;
}