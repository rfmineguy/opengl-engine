#include "instancedRenderer.h"
#include <GL/glext.h>
#include "../components/components.h"
#include "../util/geometryUtil.hpp"

//textureAtlas("test_atlas.png", 32, 32){
InstancedRenderer::InstancedRenderer()
:shader("instanced"),
textureAtlas("atlas_test") {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    Init();
}

InstancedRenderer::~InstancedRenderer() {

}

void InstancedRenderer::Init() {
    using namespace glm;
    //initQuad(geometry, {vec2(1, 0), vec2(0, 0), vec2(1, 1), vec2(0, 1)});
    int verticesSize = sizeof(geometry.mVertices[0]) * geometry.mVertices.size();
    int indicesSize = sizeof(geometry.mIndices[0]) * geometry.mIndices.size();

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesSize, geometry.mVertices.data(), GL_STREAM_DRAW);// geometry.mVertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, geometry.mIndices.data(), GL_STATIC_DRAW);

    //position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, pos));
    glEnableVertexAttribArray(0);

    //tex coord attribe
    //glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, texCoord));
    //glEnableVertexAttribArray(1);

    //texture coord vbo code
    glGenBuffers(1, &texCoordVbo);
    glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);


    size_t vec2size = sizeof(glm::vec2);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vec2size, (void*)0);

    glVertexAttribDivisor(1, 0);  //update texcoord for each vertex

    //instance vbo code
    glGenBuffers(1, &instanceMatVbo);
    glBindBuffer(GL_ARRAY_BUFFER, instanceMatVbo);

    size_t vec4Size = sizeof(glm::vec4);  //a mat4 is the size of 4 vec4s'
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

void InstancedRenderer::Draw(std::vector<GameObject>& gameObjects) {
    if (!geometrySet) {
        std::cerr << "Geometry type not set -> SetGeometry()" << std::endl;
        return;
    }

    shader.Bind();
    glBindVertexArray(vao);
    std::vector<glm::vec2> texCoords;
    std::vector<glm::mat4> matrices;

    //this might slow down the program. not sure though
    for (GameObject g : gameObjects) {
        Transform& transform = g.GetComponent<Transform>();
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, transform.position);
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
        model = glm::scale(model, transform.scale);
        model = glm::rotate(model, glm::radians(transform.rotation), glm::vec3(0, 0, 1));
        model = glm::translate(model, -glm::vec3(0.5f, 0.5f, 0.0f));
        matrices.push_back(model);

        Renderable& r = g.GetComponent<Renderable>();
        if (r.region.empty) {
            r.region = textureAtlas.GetRegion(r.textureName);
            r.region.empty = false;
        }
        //texCoords.push_back(r.region.topright);
        //texCoords.push_back(r.region.bottomright);
        //texCoords.push_back(r.region.bottomleft);
        //texCoords.push_back(r.region.topleft);
       
        texCoords.push_back(glm::vec2(0.75, 0.25));
        texCoords.push_back(glm::vec2(1.0, 1.0));
        texCoords.push_back(glm::vec2(0.0, 1.0));
        texCoords.push_back(glm::vec2(0.0, 0.0));
    }
    /*
    for (int i = 0; i < texCoords.size(); i++) {
        printf("%d - %0.4f %0.4f\n", i % 4, texCoords[i].x, texCoords[i].y);
    }
    */

    glBindBuffer(GL_ARRAY_BUFFER, instanceMatVbo);
    //std::cout << matrices.size() * sizeof(glm::mat4) << std::endl;
    glBufferData(GL_ARRAY_BUFFER, matrices.size() * sizeof(glm::mat4), &matrices[0], GL_STATIC_DRAW);
  
    glBindBuffer(GL_ARRAY_BUFFER, texCoordVbo);
    //std::cout << texCoords.size() * sizeof(glm::vec2) << std::endl;
    glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);

    textureAtlas.Bind(0);
    glBindBuffer(GL_ARRAY_BUFFER, vao);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, matrices.size());

    matrices.clear();
    texCoords.clear();
}
