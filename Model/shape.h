#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "model.h"

using namespace std;
class Scene;

enum Type {
    SQUARE  //TODO Add shapes
};



//Predefined shapes with colors and no textures
class Shape: public Object{

public:
    Shape(Type type);
    Type type;
    void render(Shader shader);

    glm::vec3 color;
    unsigned int VAO;

        //Functions to add/remove a model of a scene
    friend class Scene;

private:
    int sceneId = -1;   // = Index in the Scene array
    glm::vec3 size; //= originalSize * scale;

    void initSquare();
    void renderSquare(Shader shader);

    std::vector <float> vertices;

    unsigned int VBO, EBO;
};
