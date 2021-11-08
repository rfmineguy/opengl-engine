#pragma once
#include <glm/glm.hpp>

struct Vertex {
    Vertex(glm::vec3 _pos, glm::vec3 _col, glm::vec2 _texCoord) {
        pos = _pos;
        col = _col;
        texCoord = _texCoord;
    }
    Vertex(const Vertex& v) {
        pos = v.pos;
        col = v.col;
        texCoord = v.texCoord;
    }
    glm::vec3 pos;
    glm::vec3 col;
    glm::vec2 texCoord;
};
