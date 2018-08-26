#include <iostream>
#include "scene.h"
#include <glad/glad.h>

// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <glm/glm.hpp>
    //*****Constructors*****

Scene::Scene(){
    //Nothing for now =/
}


Scene::Scene(Shader * bindedShader){
    Scene();

    shader = bindedShader;

    bindedShader->use();
}


Scene::Scene(Camera * bindedCamera){
    Scene();

    camera = bindedCamera;
}


Scene::Scene(Shader * bindedShader, Camera * bindedCamera){
    Scene();

    shader = bindedShader;
    camera = bindedCamera;

    bindedShader->use();
}


Scene::Scene(std::string vertexPath, std::string fragmentPath){
    Scene();

    Shader bindedShader(vertexPath, fragmentPath);
    shader = &bindedShader;

    shader->use();
}


Scene::Scene(std::string vertexPath, std::string fragmentPath, Camera * bindedCamera){
    Scene();

    Shader bindedShader(vertexPath, fragmentPath);
    shader = &bindedShader;
    camera = bindedCamera;

    shader->use();
}


    //*****Member functions*****

void Scene::bindCamera(Camera * bindedCamera){
    camera = bindedCamera;
}


void Scene::bindShaders(Shader * bindedShader){
    shader = bindedShader;

    bindedShader->use();
}


void Scene::bindShadersFromPath(std::string vertexPath, std::string fragmentPath){
    Shader bindedShader(vertexPath, fragmentPath);
    shader = &bindedShader;

    shader->use();
}



void Scene::unbindShaders(){
    shader->disable();
    shader = NULL;
}


void Scene::unbindCamera(){
    camera = NULL;
}



void Scene::bindModel(Model * bindedModel){
    models.push_back(bindedModel);
    bindedModel->sceneId = models.size() - 1;
}


void Scene::unbindModel(Model * unbindedModel){
    models.erase(models.begin() + unbindedModel->sceneId);
    unbindedModel->sceneId = -1;
}



void Scene::render(){ //TODO Error management returning int

    glClearColor(0.38f, 0.71f, 1.0f, 1.0f);   //TODO Select background color, then skybox?
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setViewMatrix(camera->setView());

    for(unsigned int i=0; i<models.size(); i++){
        //Set model matrix for our model
        glm::mat4 modelMatrix = glm::mat4(1.0f);

        //1: Translate (first so the position is not re-scaled)
        modelMatrix = glm::translate(modelMatrix, models[i]->position);

        //2: Rotate
        modelMatrix = glm::rotate(modelMatrix, glm::radians(models[i]->rotationAngle), models[i]->rotationVec);

        //3:Scale
        modelMatrix = glm::scale(modelMatrix, models[i]->scale);


        shader->setModelMatrix(modelMatrix);
        models[i]->render(*shader);
    }
}
