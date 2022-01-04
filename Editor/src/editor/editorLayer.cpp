#include "editorLayer.h"
#include "util/resourceManager.h"
#include "renderer/renderer2D.h"
#include "util/random.h"
#include "imgui.h"

namespace Firefly {
EditorLayer::EditorLayer() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGuiIO& io = ImGui::GetIO();
        
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.WantSaveIniSettings = true;
       
    LOG_DEBUG("Initialized ImGuiLayer");

    LoadEditorResources();
    Renderer2D::Init();


    LOG_DEBUG("Random int test: {}", Random::RandIntRange(10, 40));
    LOG_DEBUG("Random int test: {}", Random::RandIntRange(10, 40));
    LOG_DEBUG("Random int test: {}", Random::RandIntRange(10, 40));
    LOG_DEBUG("Random int test: {}", Random::RandIntRange(10, 40));
    LOG_DEBUG("Random int test: {}", Random::RandIntRange(10, 40));

    LOG_DEBUG("Random double test: {}", Random::RandDoubleRange(10, 40));
    LOG_DEBUG("Random double test: {}", Random::RandDoubleRange(10, 40));
    LOG_DEBUG("Random double test: {}", Random::RandDoubleRange(10, 40));
    LOG_DEBUG("Random double test: {}", Random::RandDoubleRange(10, 40));
    LOG_DEBUG("Random double test: {}", Random::RandDoubleRange(10, 40));
}

EditorLayer::~EditorLayer() {
    EditorState::Serialize();
}

void EditorLayer::LoadEditorResources() {
    EditorState::Deserialize();
    ResourceManager::LoadEngineResource<Texture>("folder_icon", "../res/textures/folder.png");
    ResourceManager::LoadEngineResource<Texture>("txt_file_icon", "../res/textures/txt_file.png");
    ResourceManager::LoadEngineResource<Texture>("move_icon", "../res/textures/move.png");
    ResourceManager::LoadEngineResource<Texture>("play_icon", "../res/textures/play.png");
    ResourceManager::LoadEngineResource<Texture>("stop_icon", "../res/textures/stop.png");

    ResourceManager::LoadProjectResource<Shader>("test_shader", EditorState::CurrentProject().rootPath / "Shaders/test/");
    ResourceManager::LoadProjectResource<TextureAtlas>("spritesheet", EditorState::CurrentProject().rootPath / "Atlases/testing.atlas");

    LOG_DEBUG("Finished loading editor resources");
    Entity* e1 = EditorState::CurrentScene()->CreateEntity("Entity0");
    Entity* e2 = EditorState::CurrentScene()->CreateEntity("Entity1");
    e1->AddChild(e2);
}

//temporary game logic (until each object can have a cpp file attached)
void EditorLayer::Update() {
    Scene* scene = EditorState::CurrentScene();
    if (scene->State() == SceneState::PLAYING) {
        Entity* e = scene->FindEntity("Entity0");
        glm::vec2 worldMouse = scene->Camera().ScreenToWorld(Input.mouse);
        if (e->HasComponent<Transform>()) {
            Transform& t = e->GetComponent<Transform>();
            t.position.x = worldMouse.x;
            t.position.y = worldMouse.y;
            if (Input.IsKeyDown(GLFW_KEY_W)) {
                t.position.y--; 
            }
            if (Input.IsKeyDown(GLFW_KEY_S)) {
                t.position.y++;
            }
            if (Input.IsKeyDown(GLFW_KEY_A)) {
                t.position.x--;
            }
            if (Input.IsKeyDown(GLFW_KEY_D)) {
                t.position.x++; 
            }
        }
    }
}

void EditorLayer::ImGuiRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
  
    BeginDockspace();
    menuPanel.Draw();
    debugPanel.Draw();
    signalsPanel.Draw();
    viewportPanel.Draw();
    propertiesPanel.Draw();
    preferencesPanel.Draw();
    controlsPanel.Draw();
    scriptEditorPanel.Draw();
    sceneHeirarchyPanel.Draw();
    fileManagerPanel.Draw();
    resourcesPanel.Draw();
    logPanel.Draw();
    EndDockspace();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void EditorLayer::Cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
}
