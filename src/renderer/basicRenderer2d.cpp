#include "basicRenderer2d.h"
#include "../util/geometryUtil.hpp"
#include <glm/ext/matrix_transform.hpp>
#include "../components/components.h"

BasicRenderer2D::BasicRenderer2D()
:textureAtlas("atlas_test"),
shader("experimental") {
    textureAtlas.Print();

    initQuad(quad, textureAtlas.SubRegion(0, 0)); 
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    int verticesSize = sizeof(quad.mVertices[0]) * quad.mVertices.size();
    int indicesSize = sizeof(quad.mIndices[0]) * quad.mIndices.size();
    
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, quad.mVertices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, quad.mIndices.data(), GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, pos));
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &textureVbo);
    glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
    //tex coord attribe
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);
    glEnableVertexAttribArray(1);
}

BasicRenderer2D::~BasicRenderer2D() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    quad.mVertices.clear();
    quad.mIndices.clear();
}


//TODO : Make Renderable work
void BasicRenderer2D::Draw(std::vector<GameObject>& gameObjects) {
    drawWireframe ?
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    textureAtlas.Bind();
    shader.Bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  
    drawCalls = 0;
    for (GameObject go : gameObjects) {
        Transform& transform = go.GetComponent<Transform>();
        Renderable& renderable = go.GetComponent<Renderable>(); //contains texture coordinates into the active texture atlas via @Region

        if (renderable.region.empty) {
            renderable.region = textureAtlas.GetRegion(renderable.textureName);
            renderable.region.empty = false;
        }
        //
        //  CALCULATE MODELMATRIX
        //
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, transform.position);
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
        model = glm::scale(model, transform.scale);
        model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3(0, 0, 1));
        model = glm::translate(model, -glm::vec3(0.5f, 0.5f, 0.0f));

        //texturing
        glm::vec2 texCoord[4];
        texCoord[1] = renderable.region.topright; //topright
        texCoord[0] = renderable.region.bottomright; //bottomright
        texCoord[3] = renderable.region.bottomleft; //bottomleft
        texCoord[2] = renderable.region.topleft; //topleft

        //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, quad.mIndices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord[0]) * 4, &texCoord[0], GL_STATIC_DRAW);

        //
        //  DRAW VAO
        //
        shader.Set4fv("model", model);
        glDrawElements(GL_TRIANGLES, quad.mIndices.size(), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }
}

void BasicRenderer2D::Cleanup() {
    textureAtlas.Unbind();
    shader.Unbind();
    textureAtlas.Unbind();
}
