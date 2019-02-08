#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <vector>

using namespace std;
class Scene;
class Model;

#define NO_LIGHT_SCENE -1


//WARNING Class not implemented yet

/************************************************************************************************/

class Light{

public:
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

    Type type;
    bool renderTexture = false; //Put to true in order to render texture of custom model

    //TODO intensity, model, etc ...

        //Functions to add/remove a model of a scene
    friend class Scene;


private:
    bool isPonctual;
    int sceneId = -1;   //Id in the "lights" array in Scene structure
    Model model;

};
