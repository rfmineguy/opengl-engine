#include "editorWindow.h"

namespace Firefly {
EditorWindow::EditorWindow()
:isOpen(true) {
    
}

EditorWindow::~EditorWindow() {

}

void EditorWindow::Create(const char* title, int w, int h) {
    InitLog();
    InitWindow(title, w, h);
    InitGlad();
    InitImGui();
    stbi_set_flip_vertically_on_load(1);
    WinData.windowWidth = w;
    WinData.windowHeight = h;
    WinData.resized = true;
    Input.mouseCaptured = false;
    LOG_INFO("Created the window.");
}

void EditorWindow::Update() {
    {
        editorLayer = new EditorLayer();
        while (!glfwWindowShouldClose(window)) {
            glfwSwapBuffers(window);
            glfwPollEvents();
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            editorLayer->Update();
            editorLayer->ImGuiRender();
        }
        if (editorLayer) {
            editorLayer->Cleanup();
            delete editorLayer;
            LOG_DEBUG("Cleaning up editor layer");
        }
    }
    Cleanup();
}

void EditorWindow::Cleanup() {
    glfwDestroyWindow(window);
    glfwTerminate();
}
}

