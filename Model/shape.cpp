#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <map>
#include <vector>
#include <cmath>

#include "../Shader/shader.h"
#include "shape.h"


Shape::Shape(Type initType){
    type = initType;

    switch(type){
        case SQUARE:
            type = SQUARE;
            initSquare();
            size = glm::vec3(1.0f, 1.0f, 1.0f);
            break;

        default:
            cout << "Passed incorrect type value" << endl;
            break;
    }

}


void Shape::initSquare(){

    vertices = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };
    // first, configure the cube's VAO (and VBO)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindVertexArray(VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

}


void Shape::render(Shader shader){

    switch(type){
        case SQUARE:
            renderSquare(shader);
            break;

        default:
            cout << "Kuso" <<endl;
    }

}


void Shape::renderSquare(Shader shader){

    shader.setVec3("texture_diffuse1", color);
    shader.setVec3("lightColor",  glm::vec3(1.0f, 1.0f, 1.0f));    //WARNING Placeholder value


    //Render
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    //Reset everything
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);

}
