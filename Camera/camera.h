#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <SDL2/SDL.h>
//#include "../Window/window.h"

class Window;   //Forward declaration to avoid including file

class Camera{
    //Default camera, with FPS-like input system (ZQSD/WASD translations, mouse rotation)

private:
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);

    //Pitch goes from -90 to +90 deg
    float yaw = 90; //deg
    float pitch = 0; //deg

    glm::vec3 frontAxis = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 upAxis = glm::vec3(0.0f, 1.0f, 0.0f);


    // About mouse input system:
    // We consider that a camera does 360deg in 10 000 px
    // We also multiply all the inputs from the mouse by the rotateSpeed
    // So the camera rotates at a speed of: rotateSpeed*0.036 deg/px


public:
    Camera(glm::vec3 initPos);
    glm::mat4 setView();    //Returns viewMatrix for vertex shaders
    void move(SDL_Event event, unsigned int refreshRate);

    float movSpeed = 0.5;   // Keyboard input (unit/sec)
    float rotSpeed = 5;  // Mouse input (deg/px)

};
