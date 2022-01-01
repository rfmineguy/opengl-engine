#include "editorLayer.h"
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
}

EditorLayer::~EditorLayer() {

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
