#pragma once

#include <iostream>
#include <glm/glm.hpp>

struct Region {
    glm::vec2 topright;
    glm::vec2 topleft;
    glm::vec2 bottomright;
    glm::vec2 bottomleft;
    
    bool empty = true;
};
