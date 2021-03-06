#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "../src/stb/stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

#include "../Shader/shader.h"
#include "model.h"

using namespace std;

/************************************************************************************************/
    //Mesh class


//Constructor
Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures){
    //Binds values
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    //Creation of VAO, VBO and EBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    //Binding of VAO, VBO, EBO
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);


    //Creation of vertex array
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    //Creation of vertex normals array
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

    //Creation of texture coords array
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoords));

    //Creation of vertex tangent array
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

    //Creation of texture bitangents array
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));

    //Bind vertices
    glBindVertexArray(0);
}


void Mesh::render(Shader shader){

    //Keep track of textures
    unsigned int nDiffuse  = 1;
    unsigned int nSpecular = 1;
    unsigned int nNormal   = 1;
    unsigned int nHeight   = 1;


    for(unsigned int i = 0; i < textures.size(); i++){
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = textures[i].type;

        if(name == "texture_diffuse")
            number = std::to_string(nDiffuse++); //Transfer to stream
        else if(name == "texture_specular")
            number = std::to_string(nSpecular++); //Transfer to stream
        else if(name == "texture_normal")
            number = std::to_string(nNormal++); // Transfer to stream
         else if(name == "texture_height")
            number = std::to_string(nHeight++); // Transfer to stream

         //Render correct texture
        glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
        shader.setVec3("lightColor", glm::vec3(0.8f, 1.0f, 0.8f));
        //Bind
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    //Render
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    //Reset everything
    glBindVertexArray(0);
    glActiveTexture(GL_TEXTURE0);
}


/************************************************************************************************/
    //Model class

//Constructor

Model::Model(string path){

    Assimp::Importer import;
    path = "resources/models/" + path;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    //Create vectors to determine size of models
    glm::vec3 minCoords = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 maxCoords = glm::vec3(0.0f, 0.0f, 0.0f);
    bool firstNode = true;


    //Look for error importing file
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        cout << "ERROR (importing model): " << import.GetErrorString() << endl;
    }

    directory = path.substr(0, path.find_last_of('/'));

    //Process root node
    processNode(scene->mRootNode, scene, minCoords, maxCoords, firstNode);

    //Calculate attributes
    size = glm::vec3(abs(minCoords.x-maxCoords.x), abs(minCoords.y-maxCoords.y), abs(minCoords.z-maxCoords.z));
    offset = glm::vec3((maxCoords.x+minCoords.x)/2.0f, (maxCoords.y+minCoords.y)/2.0f, (maxCoords.z+minCoords.z)/2.0f);

    cout<<directory<<endl;

}


//Functions

void Model::render(Shader shader){


    //Loops through all meshes and render them
    for(unsigned int i = 0; i < meshes.size(); i++)
        meshes[i].render(shader);
}


void Model::processNode(aiNode *node, const aiScene *scene, glm::vec3& minCoords, glm::vec3& maxCoords, bool& firstNode){

    //If the node contains meshes
    for(unsigned int i = 0; i < node->mNumMeshes; i++){
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, minCoords, maxCoords, firstNode));
    }
    //If the node has children
    for(unsigned int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene, minCoords, maxCoords, firstNode);
    }
}


Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene, glm::vec3& minCoords, glm::vec3& maxCoords, bool& firstNode){

    //Declaration of data to gather
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;


    //Loops through all vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++){
        Vertex vertex;
        glm::vec3 vector; //Vector used as buffer

        //Vertex pos
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        if(firstNode){
            minCoords = vector;
            maxCoords = vector;
            firstNode = false;
        }

        //Keep trak of the min/max coords to determine model box
        if(vector.x < minCoords.x)
            minCoords.x = vector.x;
        else if(vector.x > maxCoords.x)
            maxCoords.x = vector.x;

        if(vector.y < minCoords.y)
            minCoords.y = vector.y;
        else if(vector.y > maxCoords.y)
            maxCoords.y = vector.y;

        if(vector.z < minCoords.z)
            minCoords.z = vector.z;
        else if(vector.z > maxCoords.z)
            maxCoords.z = vector.z;


        //Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        //Texture coords
        if(mesh->mTextureCoords[0]){ // does the mesh contain texture coordinates?

            glm::vec2 vec;
            //WARNING Assume that vertex contains one tex coord only
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);

        //Tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.tangent = vector;
        //Bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.bitangent = vector;

        vertices.push_back(vertex);
    }

    //Loops through all mesh faces
    for(unsigned int i = 0; i < mesh->mNumFaces; i++){
        aiFace face = mesh->mFaces[i];

        //Store face indices
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    //Process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    //Assumes that textures are named as follows:
    //"texture_diffuseN"
    //"texture_specularN"
    //etc..
    //Where N is a positive integer

    //Diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    //Specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    //Normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    //Height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());


    return Mesh(vertices, indices, textures);
}


vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName){
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        //Check if texture has already been loaded and can be reused
        bool skip = false;
        for(unsigned int j = 0; j < loadedTex.size(); j++){
            if(std::strcmp(loadedTex[j].path.data(), str.C_Str()) == 0){
                textures.push_back(loadedTex[j]);
                skip = true;
                break;
            }
        }
        if(!skip){   //Load tex
            Texture texture;
            texture.id = textureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            loadedTex.push_back(texture);
        }
    }
    return textures;
}


unsigned int Model::textureFromFile(const char *path, const string &directory){
    string fileName = string(path);
    fileName = directory + '/' + fileName;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nComponents;
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nComponents, 0);
    if (data){
        GLenum format;
        if (nComponents == 1)
            format = GL_RED;
        else if (nComponents == 3)
            format = GL_RGB;
        else if (nComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    } else {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
