#ifndef MODEL_H
#define MODEL_H

/**
 * An interface for a game model.
 */
class Model {
  public:
    /**
     * Interface method for rendering a model
     */
    virtual void draw() = 0;
};

#endif // MODEL_H