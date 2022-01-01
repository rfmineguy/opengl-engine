#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "core/engine/engine.h"

namespace Firefly {
class Window {
public:
    Window();
    ~Window();
    int Create(const char* title, int width, int height);
    void Update();
    void Render();
    void RenderImGui();
    void PollEvents(GLFWwindow*);
    void Cleanup();

//Initialization functions
public:
    void InitWindow(const char* title, int width, int height);
    void InitGlad();
    void InitImGui();
    void InitLogging();

private:
    bool resizeUpdate = false;

    float deltaTime;
    float lastFrame;
    GLFWwindow* window;
    int windowWidth, windowHeight;
    int lastWindowWidth, lastWindowHeight;

    Engine* engine;
};
}
