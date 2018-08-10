#pragma once

//#include <iostream>
#include <vector>
#include "../Shader/shader.h"
#include "../Camera/camera.h"
#include "../Model/model.h"

    //TODO Implement error management
#define NULL_CAMERA -1
#define NULL_SHADER -2
#define NULL_CAM_SHADER -3

class Window;

class Scene{
public:
    //Constructors
    Scene();
    Scene(Shader * bindedShader);
    Scene(Camera * bindedCamera);
    Scene(Shader * bindedShader, Camera * bindedCamera);
    Scene(std::string vertexPath, std::string fragmentPath);
    Scene(std::string vertexPath, std::string fragmentPath, Camera * bindedCamera);

    void bindCamera(Camera * bindedCamera);
    void bindShaders(Shader * bindedShader);
    void bindShadersFromPath(std::string vertexPath, std::string fragmentPath);

    void unbindShaders();
    void unbindCamera();

    void bindModel(Model * bindedModel);
    void unbindModel(Model * unbindedModel);

    void render();  //TODO Error management for this function

    friend class Window;   //Needed to access/modify camera data from the window event management

private:
    //We use classic pointers because references couldn't be NULL-initialized
    Shader * shader = NULL;
    Camera * camera = NULL;
    std::vector<Model*> models = {};

    unsigned int * refreshRate = NULL;
};
