#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "util/log.h"
#include "window/inputData.h"
#include "window/windowData.h"

#include "editor/editorLayer.h"

namespace Firefly {
struct WindowCallbacks {
    static void framebuffersizeCallback(GLFWwindow* window, int w, int h) {
        WinData.windowWidth = w;
        WinData.windowHeight = h;
        WinData.resized = true;
    }
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        if (action == GLFW_PRESS) {
            Input.keys[key] = true;
        }
        if (action == GLFW_RELEASE) {
            Input.keys[key] = false;
        }
    }
    static void cursorCallback(GLFWwindow* window, double xpos, double ypos) {
        //Input.mouse.x = xpos;
        //Input.mouse.y = ypos;
    }
    static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        Input.scrollXOffset = xoffset;
        Input.scrollYOffset = yoffset;
    }
    static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        if (action == GLFW_PRESS) {
            Input.buttons[button] = true;
        }
        if (action == GLFW_RELEASE) {
            Input.buttons[button] = false;
        }
    }
};

class EditorWindow {
public:
    EditorWindow();
    ~EditorWindow();
    void Create(const char* title, int w = 600, int h = 600); //default w: 600, h: 600
    void Update();
    void Cleanup();

private:
    void InitWindow(const char* title, int w, int h) {
        if (!glfwInit())
            LOG_CRITICAL("Failed to initialize glfw");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        wWidth = w;
        wHeight = h;
        window = glfwCreateWindow(w, h, title, NULL, NULL);
        if (!window) {
            LOG_ERROR("Failed to create glfw window");
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        LOG_INFO("Initialized glfw window.");
    }
    void InitGlad() {
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            LOG_ERROR("Error loading glad");
        }
        glViewport(0, 0, wWidth, wHeight);

        //callbacks
        glfwSetFramebufferSizeCallback(window, WindowCallbacks::framebuffersizeCallback);
        glfwSetKeyCallback(window, WindowCallbacks::keyCallback);
        glfwSetCursorPosCallback(window, WindowCallbacks::cursorCallback);
        glfwSetScrollCallback(window, WindowCallbacks::scrollCallback);
        glfwSetMouseButtonCallback(window, WindowCallbacks::mouseButtonCallback);
        Input.mouseCaptured = glfwGetInputMode(window, GLFW_CURSOR);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        LOG_INFO("Initialized glad, and callbacks.");
    }
    void InitLog() {
        Firefly::Log::Init();
    }
    void InitImGui() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        LOG_INFO("Initialized ImGui");
    }
private:
    bool isOpen;
    int wWidth, wHeight;
    GLFWwindow* window;

    EditorLayer* editorLayer;
};
    
}
