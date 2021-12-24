#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"

#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "windowData.h"
#include "inputData.h"

#include "../util/resourceManager.h"
#include "../util/log.h"

#define VERSION_MINOR 3
#define VERSION_MAJOR 3

WindowData WinData;
InputData Input;

namespace Firefly {
void framebuffersizeCallback(GLFWwindow* window, int w, int h) {
    WinData.windowWidth = w;
    WinData.windowHeight = h;
    WinData.resized = true;
}

void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        Input.keys[key] = true;
    }
    else if (action == GLFW_RELEASE) {
        Input.keys[key] = false;
    }

    if (Input.keys[GLFW_KEY_SPACE] && action != GLFW_REPEAT) {
        Input.mouseCaptured = !Input.mouseCaptured;
        if (Input.mouseCaptured) {
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    /*
    if (Input.mouseCaptured && glfwGetWindowAttrib(window, GLFW_HOVERED)) {
        Input.lastMouseX = Input.mouse.x;
        Input.lastMouseY = Input.mouse.y;
        
        if (xpos < WinData.windowWidth && xpos > 0)
            Input.mouse.x = xpos;
        if (ypos < WinData.windowHeight && ypos > 0)
            Input.mouse.y = WinData.windowHeight - ypos;
        
        Input.mouseOffsetX = Input.mouse.x - Input.lastMouseX;
        Input.mouseOffsetY = Input.mouse.y - Input.lastMouseY;
    } else {
        Input.mouseOffsetX = 0.f;
        Input.mouseOffsetY = 0.f;
    }*/
}

//xoffset is for trackpads
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Input.scrollXOffset = xoffset;
    Input.scrollYOffset = yoffset;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        Input.buttons[button] = true;
    }
    else if (action == GLFW_RELEASE) {
        Input.buttons[button] = false;
    }
}

Window::Window() {

}

Window::~Window() {

}


//      INITIALIZATION
int Window::Create(const char* title, int width, int height) {
    InitWindow(title, width, height);
    InitGlad();
    InitImGui();
    InitLogging();
    stbi_set_flip_vertically_on_load(1);
    WinData.windowWidth = width;
    WinData.windowHeight = height;
    WinData.resized = true;
    Input.mouseCaptured = false;
    return 0;
}

void Window::InitWindow(const char* title, int width, int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, VERSION_MINOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, VERSION_MAJOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    windowWidth = width;
    windowHeight = height;
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        LOG_ERROR("Error creating window");
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
}

void Window::InitGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Error loading glad");
    }
    glViewport(0, 0, windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, framebuffersizeCallback);
    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    Input.mouseCaptured = glfwGetInputMode(window, GLFW_CURSOR);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    //glEnable(GL_DEPTH_TEST);
}

void Window::InitImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}

void Window::InitLogging() {
    Log::Init();
}

//      RUNTIME
void Window::Update() {
    {
        engine = new Engine();

        bool currentTestDeleted = false;
        while (!glfwWindowShouldClose(window)) {
            Input.scrollXOffset = 0;
            Input.scrollYOffset = 0;
            WinData.frameTime = glfwGetTime();
            WinData.deltaTime = WinData.frameTime - WinData.lastFrameTime;
            WinData.spf = deltaTime;
            WinData.lastFrameTime = lastFrame;
            //poll events
            PollEvents(window);
            glfwSwapBuffers(window);

            if (WinData.resized) {
                engine->Resize(WinData.windowWidth, WinData.windowHeight);
                WinData.resized = false;
            }
            //clear screen
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
           
            //render IMGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            engine->Update(WinData.deltaTime);
            engine->Draw();
            
            RenderImGui();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        
        if (engine) {
            engine->Destroy();
            delete engine;
            LOG_INFO("Deleted engine");
        }
    }
}

void Window::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::RenderImGui() {
}

void Window::PollEvents(GLFWwindow* window) {
    glfwPollEvents();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


//      CLEANUP
void Window::Cleanup() {
    LOG_WARN("Cleaning up");
    ResourceManager::Cleanup();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
}
