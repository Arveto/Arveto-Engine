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



void Scene::bindElement(Model * bindedModel){
    ListElement newElement;
    newElement.model = bindedModel;

    models.push_back(newElement);
    bindedModel->sceneId = models.size() - 1;


}


void Scene::unbindElement(Model * unbindedModel){
    models.erase(models.begin() + unbindedModel->sceneId);
    int removalId = unbindedModel->sceneId;
    unbindedModel->sceneId = -1;

    //Update new IDs
    for(unsigned int i=removalId; i<models.size(); i++){
        if(models[i].model != NULL)
            models[i].model->sceneId --;

        else if(models[i].shape != NULL)
            models[i].shape->sceneId --;
    }
}


void Scene::bindElement(Shape * bindedShape){
    ListElement newElement;
    newElement.shape = bindedShape;

    models.push_back(newElement);
    bindedShape->sceneId = models.size() - 1;
}


void Scene::unbindElement(Shape * unbindedShape){
    models.erase(models.begin() + unbindedShape->sceneId);
    int removalId = unbindedShape->sceneId;
    unbindedShape->sceneId = -1;

    //Update new IDs
    for(unsigned int i=removalId; i<models.size(); i++){
        if(models[i].model != NULL)
            models[i].model->sceneId --;

        else if(models[i].shape != NULL)
            models[i].shape->sceneId --;
    }
}




void Scene::render(){ //TODO Error management returning int

    glClearColor(0.38f, 0.71f, 1.0f, 1.0f);   //TODO Select background color, then skybox?
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->setViewMatrix(camera->setView());

    for(unsigned int i=0; i<models.size(); i++){
        //Set model matrix for our model
        glm::mat4 modelMatrix = glm::mat4(1.0f);


        if(models[i].model != NULL){
            //1: Rotate (first so position vector does not rotate)
            modelMatrix = glm::rotate(modelMatrix, glm::radians(models[i].model->rotationAngle), models[i].model->rotationVec);

            //2: Translate (second so the position is not re-scaled)
            modelMatrix = glm::translate(modelMatrix, models[i].model->position - models[i].model->offset);

            //3:Scale
            modelMatrix = glm::scale(modelMatrix, models[i].model->scale);

            shader->setModelMatrix(modelMatrix);
            models[i].model->render(*shader);
        }

        else if(models[i].shape != NULL){
            //1: Rotate (first so position vector does not rotate)
            modelMatrix = glm::rotate(modelMatrix, glm::radians(models[i].shape->rotationAngle), models[i].shape->rotationVec);

            //2: Translate (second so the position is not re-scaled)
            modelMatrix = glm::translate(modelMatrix, models[i].shape->position);

            //3:Scale
            modelMatrix = glm::scale(modelMatrix, models[i].shape->scale);

            shader->setModelMatrix(modelMatrix);
            models[i].shape->render(*shader);
        }



    }
}
