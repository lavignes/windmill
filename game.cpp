#include "game.h"

using namespace std;

Game* Game::self = 0;
bool Game::key_presses[256];
bool Game::key_releases[256];
bool Game::key_holds[256];

void Game::keyboard_clear() {
  int i;
  for (i = 0; i < 256; i++) {
    key_presses[i] = false;
    key_releases[i] = false;
  }
}

void Game::keyboard_down(unsigned char key, int x, int y) {
  key_presses[key] = true;
  key_holds[key] = true;
  key_releases[key] = false;
}

void Game::keyboard_up(unsigned char key, int x, int y) {
  key_presses[key] = false;
  key_holds[key] = false;
  key_releases[key] = true;
}

void Game::keyboard_special_down(int key, int x, int y) {
  key_presses[key] = true;
  key_holds[key] = true;
  key_releases[key] = false;
}

void Game::keyboard_special_up(int key, int x, int y) {
  key_presses[key] = false;
  key_holds[key] = false;
  key_releases[key] = true;
}

Game* Game::instance() {
  return (self)? self : self = new Game();
}

Game::Game() {

}

Game::~Game() {

}

void Game::init(int* argc, char** argv, const string& title) {
  glutInit(argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(600, 600);
  glutInitContextVersion(3, 1);
  glutInitContextProfile(GLUT_FORWARD_COMPATIBLE);
  glutInitContextProfile(GLUT_CORE_PROFILE);
  glutCreateWindow(title.c_str());
  glewExperimental = true;
  glewInit();

  glutKeyboardFunc(keyboard_down);
  glutKeyboardUpFunc(keyboard_up);
  glutSpecialFunc(keyboard_special_down);
  glutSpecialUpFunc(keyboard_special_up);

  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void Game::run() {
  glutTimerFunc(16.6667, draw, 0);
  glutMainLoop();
}

void Game::quit() {
  glutLeaveMainLoop();
}

void Game::add_model(Model* model) {
  instance()->models.push_back(model);
}

void Game::set_step_callback(void (*callback)(void*), void* user_data) {
  instance()->step_callback = callback;
  instance()->step_data = user_data;
}

bool Game::is_key_pressed(int key) {
  return key_presses[key];
}

bool Game::is_key_released(int key) {
  return key_releases[key];
}

bool Game::is_key_held(int key) {
  return key_holds[key];
}

void Game::draw(int value) {
  if (instance()->step_callback)
    instance()->step_callback(instance()->step_data);
  keyboard_clear();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  list<Model*>::iterator m, end = instance()->models.end();
  for(m = instance()->models.begin(); m != end; m++) {
    (*m)->draw();
  }

  glutSwapBuffers();
  glutTimerFunc(16.6667, draw, 0);
}