#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"

#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>

#include "../test/test.h"
#include "../test/testClearColor.h"
#include "../test/testTriangle.h"
#include "../test/testShaderDev.h"
#include "../test/testGame.h"

#include "windowData.h"
#include "inputData.h"

#define VERSION_MINOR 3
#define VERSION_MAJOR 3

WindowData WinData;
InputData Input;

void framebuffersizeCallback(GLFWwindow* window, int w, int h) {
    glViewport(0, 0, w, h);

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
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos) {
    if (/*Input.mouseCaptured &&*/ glfwGetWindowAttrib(window, GLFW_HOVERED)) {
        Input.lastMouseX = Input.mouseX;
        Input.lastMouseY = Input.mouseY;
        
        if (xpos < WinData.windowWidth && xpos > 0)
            Input.mouseX = xpos;
        if (ypos < WinData.windowHeight && ypos > 0)
            Input.mouseY = ypos;
        
        Input.mouseOffsetX = Input.mouseX - Input.lastMouseX;
        Input.mouseOffsetY = Input.mouseY - Input.lastMouseY;
    } else {
        Input.mouseOffsetX = 0.f;
        Input.mouseOffsetY = 0.f;
    }
}

//xoffset is for trackpads
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    Input.scrollXOffset = xoffset;
    Input.scrollYOffset = yoffset;
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS) {
        Input.mouse[button] = true;
    }
    else if (action == GLFW_RELEASE) {
        Input.mouse[button] = false;
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

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    windowWidth = width;
    windowHeight = height;
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (window == NULL) {
        std::cerr << "Failed to create Window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
}

void Window::InitGlad() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to load Glad properly" << std::endl;
    }
    glViewport(0, 0, windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, framebuffersizeCallback);
    glfwSetKeyCallback(window, keyboardCallback);
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    Input.mouseCaptured = glfwGetInputMode(window, GLFW_CURSOR);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glEnable(GL_DEPTH_TEST);
}

void Window::InitImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
}


//      RUNTIME
void Window::Update() {
    {
        test::Test* currentTest = nullptr;
        test::TestMenu* testMenu = new test::TestMenu(currentTest);
        currentTest = testMenu;

        testMenu->RegisterTest<test::TestClearColor>("Clear Color");
        testMenu->RegisterTest<test::TestTriangle>("Test Triangle");
        testMenu->RegisterTest<test::TestShaderDev>("Test Shader Dev");
        testMenu->RegisterTest<test::TestGame>("Test Game");

        while (!glfwWindowShouldClose(window)) {

            Input.scrollXOffset = 0;
            Input.scrollYOffset = 0;
            WinData.frameTime = glfwGetTime();
            WinData.deltaTime = WinData.frameTime - WinData.lastFrameTime;
            WinData.spf = deltaTime;
            WinData.lastFrameTime = lastFrame;
            //poll events
            PollEvents(window, currentTest);
            glfwSwapBuffers(window);

            if (WinData.resized) {
                currentTest->Resize(WinData.windowWidth, WinData.windowHeight);
                WinData.resized = false;
            }
            //clear screen
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
           
            //currentTest.Resize(windowWidth, windowHeight);

            //render IMGUI
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            if (currentTest) {
                currentTest->Update(WinData.deltaTime);
                currentTest->Render();
                ImGui::Begin("Test");
                
                if (currentTest != testMenu && ImGui::Button("<-")) {
                    delete currentTest;
                    currentTest = testMenu;
                }

                currentTest->ImGuiRender();
                if (currentTest == testMenu && ImGui::Button("Exit")) {
                    glfwSetWindowShouldClose(window, true);
                } 
                
                ImGui::End();
            }
            RenderImGui();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }
        
        //program segfaults here sometimes for some reason
        //  reason : 
        //      - compiler automatically deletes stack allocated pointers
        //        (i.e currentTest) and when I deleted it, it no longer existed
        //        for the compiler to delete
        if (testMenu) {
            delete testMenu;
            std::cout << "Deleted testmenu" << std::endl;
        }
    }
}

void Window::Render() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::RenderImGui() {
}

void Window::PollEvents(GLFWwindow* window, test::Test* test) {
    glfwPollEvents();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


//      CLEANUP
void Window::Cleanup() {
    std::cout << "Cleaning up" << std::endl;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
