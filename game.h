/**
 * game.h: A class for managing the game state.
 * @author Scott LaVigne
 */
#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/freeglut_ext.h>

#include <list>
#include <string>

#include "model.h"

/**
 * A singleton for managing a game
 */
class Game {
  public:
    /**
     * Get the singleton instance for the game.
     * @return The single game instance
     */
    static Game* instance();

    /**
     * Destructor
     */
    ~Game();

    /**
     * Initialize the game.
     * @param argc  a reference to the system's argc
     * @param argv  the system's argv
     * @param title window title to use
     */
    static void init(int* argc, char** argv, const std::string& title);

    /**
     * Start the game.
     */
    static void run();

    /**
     * Quit the game.
     */
    static void quit();

    /**
     * Add a model to render each frame.
     * @param model a model.
     */
    static void add_model(Model* model);

    /**
     * Set the method that will be ran every frame.
     * @param callback  a void function taking a void* argument
     * @param user_data optional data to pass to the function
     *                  every frame
     */
    static void set_step_callback(void (*callback)(void*), void* user_data = 0);

    /**
     * Test if a given key is being pressed this frame.
     * @param  key the key to test
     * @return     true if the key has just been pressed this frame
     */
    static bool is_key_pressed(int key);

    /**
     * Test if a given key is being released this frame.
     * @param  key the key to test
     * @return     true if the key has just been released this frame
     */
    static bool is_key_released(int key);

    /**
     * Test if a given key is being held this frame.
     * A key is considered "held" if it has been pressed for two or more
     * consecutive frames.
     * @param  key the key to test
     * @return     true if the key is currently being held
     */
    static bool is_key_held(int key);

  private:
    Game();
    static void draw(int);

    std::list<Model*> models;
    void (*step_callback)(void*);
    void* step_data;
    static Game* self;

    static void keyboard_clear();
    static void keyboard_down(unsigned char, int, int);
    static void keyboard_up(unsigned char, int, int);
    static void keyboard_special_down(int, int, int);
    static void keyboard_special_up(int, int, int);
    static bool key_presses[];
    static bool key_releases[];
    static bool key_holds[];
};

#endif // GAME_H