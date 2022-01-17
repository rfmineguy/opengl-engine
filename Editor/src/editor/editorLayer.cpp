#include "editorLayer.h"
#include "util/resourceManager.h"
#include "util/random.h"
#include "util/cppUtil.h"
#include "imgui.h"
#include "ImGuizmo/ImGuizmo.h"

namespace Firefly {
EditorLayer::EditorLayer() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGuiIO& io = ImGui::GetIO();
        
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.WantSaveIniSettings = true;
       
    LOG_DEBUG("Initialized ImGuiLayer");

    LoadEditorResources();

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

    //load editor resources
    ResourceManager::LoadEngineResource<Texture>("folder_icon", "res/textures/folder.png");
    ResourceManager::LoadEngineResource<Texture>("txt_file_icon", "res/textures/txt_file.png");
    ResourceManager::LoadEngineResource<Texture>("move_icon", "res/textures/moveIcon.png");
    ResourceManager::LoadEngineResource<Texture>("rotate_icon", "res/textures/rotateIcon.png");
    ResourceManager::LoadEngineResource<Texture>("scale_icon", "res/textures/resizeIcon.png");
    ResourceManager::LoadEngineResource<Texture>("play_icon", "res/textures/play.png");
    ResourceManager::LoadEngineResource<Texture>("stop_icon", "res/textures/stop.png");
    LOG_DEBUG("Finished loading editor resources");

    Entity* e1 = EditorState::CurrentScene()->CreateEntity("Entity0");
    e1->GetComponent<Transform>().position = glm::vec3(100, 100, 0);
    Entity* e2 = EditorState::CurrentScene()->CreateEntity("Entity1");
    e2->GetComponent<Transform>().position = glm::vec3(300, 100, 0);
    e1->AddChild(e2);
}

//temporary game logic (until each object can have a cpp file attached)
void EditorLayer::Update() {
    Scene* scene = EditorState::CurrentScene();
    if (EditorState::CurrentProject().isOpen && scene->State() == SceneState::PLAYING) {
        scene->Update(1/60.0f);

        Entity* e = EditorState::CurrentScene()->FindEntity("Entity0");
        if (e->HasComponent<Transform>()) {
            glm::vec2 worldMouse = scene->Camera().ScreenToWorld(Input.mouse);
            Transform& t = e->GetComponent<Transform>();
            t.position.x = worldMouse.x;
            t.position.y = worldMouse.y;
        }
    }
}

void EditorLayer::ImGuiRender() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();
  
    BeginDockspace();
    menuPanel.Draw();
    debugPanel.Draw();
    signalsPanel.Draw();

    //viewport panel draws the scene
    if (EditorState::CurrentProject().isOpen) {
        viewportPanel.Draw();
    }
    propertiesPanel.Draw();
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
