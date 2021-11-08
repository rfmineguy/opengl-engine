#include "basicRenderer2d.h"
#include "../util/geometryUtil.hpp"
//#include "../util/randomUtil.h"
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

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, col));
    glEnableVertexAttribArray(1);

    //tex coord attribe
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, texCoord));
    glEnableVertexAttribArray(2);
}

BasicRenderer2D::~BasicRenderer2D() {
    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    quad.mVertices.clear();
    quad.mIndices.clear();
}

/*
void BasicRenderer2D::AddTransform(Transform& transform) {
    transforms.push_back(transform);
}
*/

void BasicRenderer2D::Draw(entt::registry& reg) {
    textureAtlas.Bind();
    shader.Bind();
    glBindVertexArray(vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
   
    drawCalls = 0; 
    auto view = reg.view<Transform>();
    for (auto entity : view) {
        auto &transform = view.get<Transform>(entity);
        
        //
        //  CALCULATE MODELMATRIX
        //
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, transform.position);
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
        model = glm::scale(model, transform.scale);
        model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3(0, 0, 1));
        model = glm::translate(model, -glm::vec3(0.5f, 0.5f, 0.0f));

        //
        //  DRAW VAO
        //
        shader.Set4fv("model", model);
        glDrawElements(GL_TRIANGLES, quad.mIndices.size(), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }
    

/*
    for (int i = 0; i < transforms.size(); i++) {
        glm::mat4 model = glm::mat4(1.0);

        //1 translate to position
        //2 translate to center of sprite
        //3 scale
        //4 rotate
        //5 translate back to corner of sprite
        model = glm::translate(model, transforms[i].pos);
        model = glm::translate(model, transforms[i].centerOffset);
        model = glm::scale(model, transforms[i].scale);
        model = glm::rotate(model, glm::radians(transforms[i].rotation), glm::vec3(0, 0, 1));
        model = glm::translate(model, -transforms[i].centerOffset);
        shader.Set4fv("model", model);
        glDrawElements(GL_TRIANGLES, quad.mIndices.size(), GL_UNSIGNED_INT, 0);
        drawCalls++;
    }
    */
}
