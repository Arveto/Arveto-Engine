#pragma once

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
class Scene;

#define NO_SCENE -1 //Value for the sceneId of Model class


/************************************************************************************************/


struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    glm::vec3 bitangent;
};

struct Texture{
    unsigned int id;
    string type;
    string path;
};


/************************************************************************************************/


//Class used to store all mesh data
//Belongs to a Model class
class Mesh{

public:
    //Mesh
    std::vector <Vertex> vertices;
    std::vector <unsigned int> indices;
    std::vector <Texture> textures;
    unsigned int VAO;

    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
    void render(Shader shader);

private:
    unsigned int VBO, EBO;

};


/************************************************************************************************/


//Contains mesh, texture data, as well as position
//TODO: CSS like attributes
class Model{

public:
    Model(string path); //Path from 'resources/models'
    void render(Shader shader);
    vector<Texture> loadedTex;

        //Render parameters
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotationVec = glm::vec3(1.0f, 0.0f, 0.0f);   //WARNING 1.0 equals a 90 deg rotation
    float rotationAngle = -0.0f;
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);     //Size factor

    glm::vec3 getSize();    //Return curent dimensions of model
    void setSize(glm::vec3 newSize);




        //Functions to add/remove a model of a scene
    friend class Scene;

private:
    vector <Mesh> meshes;
    string directory;
    int sceneId = -1;    //Stores the index in the scene "models" array, for quick removal/acces from Scene

    void processNode(aiNode *node, const aiScene *scene, glm::vec3& minCoords, glm::vec3& maxCoords);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene, glm::vec3& minCoords, glm::vec3& maxCoords);

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    unsigned int textureFromFile(const char *path, const string &directory);


    glm::vec3 size;     //Original size of model

};
