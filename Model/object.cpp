#include "object.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <map>
#include <vector>
#include <cmath>



void Object::setSize(glm::vec3 newSize){
    size = newSize;
    scale = size / originalSize;
}

void Object::getSize(){
    return size;
}
