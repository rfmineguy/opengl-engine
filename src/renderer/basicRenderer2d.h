#pragma once
#include <vector>

#include "../render_data/geometry.h"
#include "../render_data/shader.h"
#include "../render_data/textureAtlas.h"
#include "orthoCamera.h"
#include "../game_object/gameObject.h"

#include "entt/entt.hpp"

class BasicRenderer2D {
public:
    BasicRenderer2D();
    ~BasicRenderer2D();

    void Init();
    void Draw(std::vector<GameObject>& gameObjects);
    Shader* GetShader() { return shader; }
    void Cleanup();
public:
    unsigned int drawCalls;
    bool drawWireframe = false;

private:
    Geometry quad;
    Shader* shader;
    TextureAtlas* textureAtlas;
    unsigned int vao, vbo, ebo;
    unsigned int textureVbo;
};
