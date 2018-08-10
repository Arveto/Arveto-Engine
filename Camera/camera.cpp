#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

#include "camera.h"
#include "../Window/window.h"


Camera::Camera(glm::vec3 initPos){
    pos = initPos;

    //Used to get mouse movements
    SDL_SetRelativeMouseMode(SDL_TRUE);
}


glm::mat4 Camera::setView(){
    return glm::lookAt(pos, pos + frontAxis, upAxis);
}


void Camera::move(SDL_Event event, unsigned int refreshRate){
    //This method will be called inside Window.pollEvents after the Camera object being binded

        // ***Rotation***
    if(event.type == SDL_MOUSEMOTION){
        float Xmov = event.motion.xrel * rotSpeed;
        float Ymov = event.motion.yrel * rotSpeed;

        //See camera.h for infos about rotation system
        yaw = fmod(yaw + Xmov * 0.036, 360);
        pitch += Ymov * 0.036;

        //At 90 deg, the view reverses, so we use an inferior value
        if(pitch > 89.99f)
            pitch =  89.99f;
        if(pitch < -89.99f)
            pitch = -89.99f;

        glm::vec3 newFront;
        newFront.x = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        newFront.y = -sin(glm::radians(pitch));
        newFront.z = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        frontAxis = glm::normalize(newFront);
    }

        // ***Translations***

    float timeDivision =  1.0 / refreshRate;

    const Uint8 *keystates = SDL_GetKeyboardState( NULL );

    if(keystates[SDL_SCANCODE_W])   //Forward
        //pos.z -= movSpeed * timeDivision;
        pos = pos + frontAxis * movSpeed * timeDivision;

    if(keystates[SDL_SCANCODE_A])   //Left
        pos = pos - glm::normalize(glm::cross(frontAxis, upAxis)) * movSpeed * timeDivision;

    if(keystates[SDL_SCANCODE_S])   //Backward
        pos = pos - frontAxis * movSpeed * timeDivision;

    if(keystates[SDL_SCANCODE_D])   //Right
        pos = pos + glm::normalize(glm::cross(frontAxis, upAxis)) * movSpeed * timeDivision;

    // //WARNING When moving in diagonal, both vectors are added, resulting in a higher movement speed

}
