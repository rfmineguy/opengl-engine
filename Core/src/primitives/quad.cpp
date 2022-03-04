#include "quad.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Firefly {
    Quad::Quad() {
        using namespace glm;
        vertices.push_back({ vec3 ( 1.0f,  1.0f, 0.0f ), vec2(1.0f, 1.0f) }); 
        vertices.push_back({ vec3 ( 1.0f,  0.0f, 0.0f ), vec2(1.0f, 0.0f) }); 
        vertices.push_back({ vec3 ( 0.0f,  0.0f, 0.0f ), vec2(0.0f, 0.0f) }); 
        vertices.push_back({ vec3 ( 0.0f,  1.0f, 0.0f ), vec2(0.0f, 1.0f) }); 

        indices = {0, 1, 3, 1, 2, 3};

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ebo);

        int verticesByteSize = sizeof(Vertex) * vertices.size();
        int indicesByteSize = sizeof(unsigned int) * indices.size();

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, verticesByteSize, vertices.data(), GL_STATIC_DRAW);
    
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesByteSize, indices.data(), GL_STATIC_DRAW);
    
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, pos));
        glEnableVertexAttribArray(0);

        glGenBuffers(1, &texVbo);
        glBindBuffer(GL_ARRAY_BUFFER, texVbo);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);
        glEnableVertexAttribArray(1);
    }

    Quad::~Quad() {
        glDeleteVertexArrays(1, &vao);
        glDeleteBuffers(1, &vbo);
        glDeleteBuffers(1, &ebo);
        glDeleteBuffers(1, &texVbo);
        vertices.clear();
        indices.clear();
    }
    
    void Quad::Bind() {
        glBindVertexArray(vao);
    }

    void Quad::Unbind() {
        glBindVertexArray(0);
    }
}
