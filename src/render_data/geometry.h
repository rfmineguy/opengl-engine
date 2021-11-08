#pragma once
#include <glad/glad.h>
#include "vertex.h"
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

enum GeometryType {
    QUAD,
    CUBE
};

class Geometry {
public:
    Geometry();
    ~Geometry();
    void AddVertex(Vertex v);
    void SetElements(std::vector<unsigned int> indices);
    
    //called from geometryUtil.hpp once the vetices are finished being supplied
    void Bake();

    Vertex& GetVertex(int index);
    unsigned int GetElement(int index);  //unimplemented

    void Print();
    
    //set position of geometry
    Geometry& SetPosition(int x, int y);
    
    Geometry& Rotate(float rotation);

    //move each vertex over by dx, dy
    Geometry& Translate(int dx, int dy, int dz = 0);

    //scale the geometry via its center
    Geometry& Size(float width, float height);
public:
    GeometryType type;

    std::vector<Vertex> mVertices;
    std::vector<unsigned int> mIndices;

    glm::vec2 size;
    glm::vec3 position;
    glm::vec2 scale;
    glm::mat4 model;
};
