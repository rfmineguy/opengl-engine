#pragma once

#include <glm/glm.hpp>
#include <iostream>

struct Region {
    glm::vec2 topleft;
    glm::vec2 bottomright;
    
    void Print() {
        printf("(%0.4f %0.4f) (%0.4f %0.4f)\n", 
                topleft.x, topleft.y,
                bottomright.x, bottomright.y);
    }
};
