/**
 * windmill.h: A windmill model
 * @author Scott LaVigne
 */
#ifndef WINDMILL_H
#define WINDMILL_H

#include "model.h"
#include "shader.h"
#include "maths.h"

/**
 * Windmill model.
 * Fills Model interface.
 */
class Windmill: public Model {
  public:
    /**
     * Constructor.
     * @param program A shader program to coopt.
     */
    Windmill(Pipeline* program);

    /**
     * Destructor.
     */
    virtual ~Windmill();

    /**
     * Render windmill.
     */
    void draw();

    /**
     * Get windmill blades angle.
     * @return angle in degrees
     */
    float get_blade_angle() const;

    /**
     * Set windmill blades angle.
     * @param angle an angle in degrees
     */
    void set_blade_angle(float angle);

    /**
     * Get windmill angle on x-axis.
     * @return angle in degrees
     */
    float get_angle_x() const;

    /**
     * Set windmill angle on x-axis.
     * @return angle in degrees
     */
    void set_angle_x(float angle);

    /**
     * Get windmill angle on y-axis.
     * @return angle in degrees
     */
    float get_angle_y() const;

    /**
     * Set windmill angle on y-axis.
     * @return angle in degrees
     */
    void set_angle_y(float angle);

    /**
     * Get windmill angle on z-axis.
     * @return angle in degrees
     */
    float get_angle_z() const;

    /**
     * Set windmill angle on z-axis.
     * @return angle in degrees
     */
    void set_angle_z(float angle);

  protected:
    const static vec3 BLUE;
    const static vec3 RED;
    const static vec3 GREEN;
    const static vec3 CYAN;
    const static vec3 MAGENTA;
    const static vec3 YELLOW;

    const static mat4 scale_post;
    const static mat4 scale_blade;

    Pipeline* program;
    const static vec3 cube[36];
    unsigned cube_vbo;
    unsigned vao;

    mat4 rot;
    float angle_blades;

    float angle_x_post;
    float angle_y_post;
    float angle_z_post;
};

#endif // WINDMILL_H