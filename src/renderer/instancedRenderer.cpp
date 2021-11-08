#include "instancedRenderer.h"
#include <GL/glext.h>

//textureAtlas("test_atlas.png", 32, 32){
InstancedRenderer::InstancedRenderer()
:shader("instanced") {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glGenBuffers(1, &buffer);
}

InstancedRenderer::~InstancedRenderer() {

}

void InstancedRenderer::SetGeometry(Geometry geometry) {
    int verticesSize = sizeof(geometry.mVertices[0]) * geometry.mVertices.size();
    int indicesSize = sizeof(geometry.mIndices[0]) * geometry.mIndices.size();

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, geometry.mVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, geometry.mIndices.data(), GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, pos));
    glEnableVertexAttribArray(0);

    //tex coord attribe
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, texCoord));
    glEnableVertexAttribArray(2);

    //a mat4 is the size of 4 vec4's
    size_t vec4Size = sizeof(glm::vec4);
    glEnableVertexAttribArray(3); 
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
    glEnableVertexAttribArray(4); 
    glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
    glEnableVertexAttribArray(5); 
    glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
    glEnableVertexAttribArray(6); 
    glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));

    glVertexAttribDivisor(3, 1);
    glVertexAttribDivisor(4, 1);
    glVertexAttribDivisor(5, 1);
    glVertexAttribDivisor(6, 1);   

    glBindVertexArray(0);
    geometrySet = true;
    std::cout << "Set geometry" << std::endl;
}

void InstancedRenderer::UploadModelMatrix(glm::mat4& matrix) {
    modelMatrices.push_back(matrix);
    if (modelMatrices.size() == INSTANCE_COUNT) {
        glBindBuffer(GL_ARRAY_BUFFER, buffer);
        glBufferData(GL_ARRAY_BUFFER, modelMatrices.size() * sizeof(glm::mat4), modelMatrices.data(), GL_STATIC_DRAW);
        std::cout << "modelMatrices full" << std::endl;
    }
}

void InstancedRenderer::Draw() {
    if (!geometrySet) {
        std::cerr << "Geometry type not set -> SetGeometry()" << std::endl;
        return;
    }

    shader.Bind();
    std::cout << "Texture atlas unused" << std::endl;
    //textureAtlas.Bind();
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, INSTANCE_COUNT);
}
