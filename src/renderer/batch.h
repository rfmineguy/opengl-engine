#pragma once

#include "../render_data/vertex.h"
#include "../render_data/geometry.h"
#include "../render_data/shader.h"
#include "../render_data/textureAtlas.h"

#include <vector>

class Batch {
public:
    Batch();
    ~Batch();
    void Begin(bool wireframe);
    void Add(Geometry& geometry);
    void Print();
    void Flush();
    void SetShader(std::string shader);
    Shader& GetShader();
    TextureAtlas& Atlas();
    int Size();

private:
    bool isFlushed, isWireframeDraw;
    int batchCount;
    int lastIndice = 0;
    int geometryCount = 0;

private:
    class Shader shader;
    //TextureAtlas textureAtlas;
    unsigned int vbo, ebo, vao;
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    int verticesSize, indicesSize;
};
