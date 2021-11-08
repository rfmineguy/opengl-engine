#include "batch.h"
#include <iostream>

//textureAtlas("test_atlas.png", 32, 32)
Batch::Batch()
:isFlushed(false),
shader("experimental")
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    std::cout << "Vertex Array Object : " << vao << std::endl;
    std::cout << "Vertex Buffer Object : " << vbo << std::endl;
    std::cout << "Element Buffer Object : " << ebo << std::endl;
    glBindVertexArray(vao);
}

Batch::~Batch() {
    vertices.clear();
    indices.clear();
    shader.Unbind();

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
}

void Batch::Begin(bool wireframe) {
    isFlushed = false;
    isWireframeDraw = wireframe;
}

//indices are more complex than this for batching
void Batch::Add(Geometry& geometry) {
    if (isFlushed) {
        std::cerr << "Batch must be flushed before adding new geometry" << std::endl;
    }
    //std::cout << geometry.mVertices.size() << sizeof(Vertex) << std::endl; 
    for (int i = 0; i < geometry.mVertices.size(); i++) {
        vertices.push_back(geometry.mVertices[i]);
    }

    //
    //  When adding a second Geometry the indices should reflect that
    //
    for (int i = 0; i < geometry.mIndices.size(); i++) {
        indices.push_back(geometry.mIndices[i] + lastIndice);
    }
    lastIndice += geometry.mVertices.size();

    geometryCount++;
}

void Batch::Print() {
    for (int i = 0; i < vertices.size(); i++) {
        Vertex v = vertices.at(i);
        printf("{x=%0.4f y=%0.4f z=%0.4f}\n", v.pos.x, v.pos.y, v.pos.z);
    }

    for (int i = 0; i < indices.size(); i+=6) {
        printf("[%d %d %d %d %d %d]\n", indices[i], indices[i+1], indices[i+2], indices[i+3], indices[i+4], indices[i+5]);
    }
}

void Batch::Flush() {
    if (isWireframeDraw) glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else                 glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if (isFlushed) {
        std::cerr << "Batch empty, use Add(Geometry&) to fill it up" << std::endl;
        return;
    }

    glBindVertexArray(vao);

    verticesSize = sizeof(vertices[0]) * vertices.size();
    indicesSize = sizeof(indices[0]) * indices.size();

    //std::cout << verticesSize << "   " << indicesSize << std::endl;

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices.data(), GL_DYNAMIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices.data(), GL_DYNAMIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, pos));
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, col));
    glEnableVertexAttribArray(1);

    //tex coord attribe
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, texCoord));
    glEnableVertexAttribArray(2);
    
    /* TODO
    in order for this texture to work we need to add things to the shader
    program
    */
    //textureAtlas.Bind();
    std::cout << "WARNING : Texture Atlas is commented out, not used in this test" << std::endl; 
    shader.Bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo); //overkill? already bound from above?
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    vertices.clear();
    indices.clear();
    lastIndice = 0;
    geometryCount = 0;
    isFlushed = true;
}

void Batch::SetShader(std::string tag) {
    shader.CleanAndChange(tag);
}

Shader& Batch::GetShader() {
    return shader;
}
/*
TextureAtlas& Batch::Atlas() {
    return ;
    //return textureAtlas;
}
*/

int Batch::Size() {
    return geometryCount; 
}
