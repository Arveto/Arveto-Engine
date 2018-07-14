#pragma once

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>

#include "../Window/window.h"


class Camera{
    private:
        glm::vec3 frontAxis = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 upAxis = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

        float timeDivision;
        float movSpeed = 0.5;   // units/sec
        // float rotateSpeed;  --> For uncoming mouse (orientation) input



    public:
        Camera(glm::vec3 initPos, Window &window);
        glm::mat4 setView();    //Returns viewMatrix for vertex shaders
        void move();

};
