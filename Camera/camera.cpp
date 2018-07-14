#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include "camera.h"


Camera::Camera(glm::vec3 initPos, Window &window){
    pos = initPos;
    timeDivision = window.getRefreshRate() / 1000.0;
}


glm::mat4 Camera::setView(){
    return glm::lookAt(pos, pos + frontAxis, upAxis);
}


void Camera::move(){
    const Uint8 *keystates = SDL_GetKeyboardState( NULL );


    if(keystates[SDL_SCANCODE_W])
        pos.z -= movSpeed * timeDivision;

    if(keystates[SDL_SCANCODE_A])
        pos.x -= movSpeed * timeDivision;

    if(keystates[SDL_SCANCODE_S])
        pos.z += movSpeed * timeDivision;

    if(keystates[SDL_SCANCODE_D])
        pos.x += movSpeed * timeDivision;
}
