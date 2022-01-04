#pragma once

#include "core/corepch.h"
#include "core/entity/entity.h"
//#include "core/engine/imguilayer.h"
#include "util/resourceManager.h"
#include "renderer/orthoCamera.h"
#include "window/inputData.h"
#include "window/windowData.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Firefly {
class Engine {
public:
    Engine();
    ~Engine();
    void Create();
    void Destroy();
    void Update(float dt);
    void Draw();
    void Resize(int width, int height);

private:
    OrthoCamera camera;
    Scene* currentScene;
};
}