#pragma once
#include "../render_data/geometry.h"
#include "../render_data/shader.h"
#include "../render_data/textureAtlas.h"
#include "orthoCamera.h"
#include "entt/entt.hpp"

class BasicRenderer2D {
public:
    BasicRenderer2D();
    ~BasicRenderer2D();
    //void AddTransform(Transform& transform);
    void Draw(entt::registry& reg);
    Shader& GetShader() { return shader; }
    TextureAtlas& Atlas() { return textureAtlas; }

public:
    unsigned int drawCalls;

private:
    Geometry quad;
    Shader shader;
    TextureAtlas textureAtlas;
    unsigned int vao, vbo, ebo;
    //std::vector<Transform> transforms;
    std::vector<glm::mat4> modelMatrices;
};
