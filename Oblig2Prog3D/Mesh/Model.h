// #pragma once
// #include <vector>
//
// #include "Mesh.h"
// #include "../Shader.h"
// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>
//
// class Model
// {
// public:
//     Model(std::string path)
//     {
//         loadModel(path);
//     }
//     void Draw(shadertest &shader);	
// private:
//     // model data
//     std::vector<Mesh> meshes;
//     std::string directory;
//
//     unsigned int TextureFromFile(std::string path, std::string directory);
//     void loadModel(std::string path);
//     void processNode(aiNode *node, const aiScene *scene);
//     Mesh processMesh(aiMesh *mesh, const aiScene *scene);
//     std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
//                                               std::string typeName);
//     
// };
