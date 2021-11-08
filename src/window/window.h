#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../test/test.h"

class Window {
public:
    Window();
    ~Window();
    int Create(const char* title, int width, int height);
    void Update();
    void UpdateTest(test::Test* currentTest, test::TestMenu*&, bool);
    void Render();
    void RenderImGui();
    void PollEvents(GLFWwindow*, test::Test*);
    void Cleanup();

//Initialization functions
public:
    void InitWindow(const char* title, int width, int height);
    void InitGlad();
    void InitImGui();

private:
    bool resizeUpdate = false;

    float deltaTime;
    float lastFrame;
    GLFWwindow* window;
    int windowWidth, windowHeight;
    int lastWindowWidth, lastWindowHeight;
};
