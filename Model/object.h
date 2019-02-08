#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>

class Scene;


//TODO: CSS like attributes
class Object{

public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

        //Effective rotation = rotationAngle * rotationVec (deg)
    glm::vec3 rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);
    float rotationAngle = -0.0f;

    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);     //Size factor

    void setSize(glm::vec3 newSize);
    glm::vec3 getSize();    //Return curent dimensions of model


private:
    glm::vec3 originalSize;

    Scene * parentScene = NULL;    //Needed at render time

};
