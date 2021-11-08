#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <string>

/* Transform component
 *   position, scale, rotation
 */
struct Transform {
    glm::vec3 position;
    glm::vec3 scale;
    float rotation; 

    Transform(float x, float y, float xscale, float yscale, float _rotation) {
        position = glm::vec3(x, y, 0);
        scale = glm::vec3(xscale, yscale, 1);
        rotation = _rotation;
    }

    Transform(glm::vec3 _position, glm::vec3 _scale, float _rotation) {
        position = _position;
        scale = _scale;
        rotation = _rotation;
    }

    void Print() {
        printf("pos {%0.4f %0.4f}, scale {%0.4f %0.4f %0.4f}, rot {%0.4f}\n",
                position.x, position.y,
                scale.x, scale.y, scale.z,
                rotation);
    }
};

/* Identifier component
 *   meant as a way to retrieve an entity by a unique id
 */
struct Identifier {
    std::string id;
};

/* SpriteRenderer component
 *   meant as a container for rendering a given geometry
 *   WIP - not sure how to design this
 */
struct SpriteRenderer {

};

/* Animator component
 *   a controller for the sprite renderer (dependent on it)
 *   the sprite renderer must have a spritesheet
 */
struct Animator {
    float speed;
    int currentFrame;
    int nextFrame;
    bool looping;
};
