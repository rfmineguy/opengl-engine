#include "editorLayer.h"
#include "util/resourceManager.h"
#include "imgui.h"

namespace Firefly {
EditorLayer::EditorLayer() {
    const ImGuiViewport* viewport = ImGui::GetMainViewport();

    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGuiIO& io = ImGui::GetIO();
        
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.WantSaveIniSettings = true;
    //ImGuiLayer::Get().font = io.Fonts->AddFontFromFileTTF("res/engine_files/fonts/Montserrat-Light.tff", 16.0f);
    //io.ConfigDockingWithShift = true;
       
    LOG_DEBUG("Initialized ImGuiLayer");

    LoadEditorResources();
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

    ResourceManager::LoadProjectResource<TextureAtlas>("spritesheet", EditorState::CurrentProject().rootPath / "Atlases/testing.atlas");

    LOG_DEBUG("Finished loading editor resources");
    EditorState::CurrentScene()->CreateEntity("Entity0");
    EditorState::CurrentScene()->CreateEntity("Entity1");
}

void EditorLayer::Update() {

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
