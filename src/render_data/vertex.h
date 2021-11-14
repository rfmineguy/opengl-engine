#pragma once
#include <glm/glm.hpp>

struct Vertex {
    Vertex(glm::vec3 _pos, glm::vec2 _texCoord) {
        pos = _pos;
        texCoord = _texCoord;
    }
    Vertex(const Vertex& v) {
        pos = v.pos;
        texCoord = v.texCoord;
    }
    glm::vec3 pos;      //12 bytes
    glm::vec2 texCoord; //8 bytes
                        //20 bytes
};
