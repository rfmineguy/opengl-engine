#pragma once

#include "imgui.h"
#include "window/windowData.h"
#include "stb/stb_image.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "imguiMenuPanel.hpp"
#include "imguiDebugPanel.hpp"
#include "imguiSignalsPanel.hpp"
#include "imguiViewportPanel.hpp"
#include "imguiPropertiesPanel.hpp"
#include "imguiPreferencesPanel.hpp"
#include "imguiControlsBarPanel.hpp"
#include "imguiScriptEditorPanel.hpp"
#include "imguiSceneHeirarchyPanel.hpp"
#include "imguiFileManagerPanel.hpp"
#include "imguiResourcesPanel.hpp"
#include "imguiLogPanel.hpp"

namespace Firefly {
class EditorLayer {
public:
    EditorLayer();
    ~EditorLayer();
    void LoadEditorResources();
    void Update();
    void ImGuiRender();

    void Cleanup();

private:
    void BeginDockspace() {
        static bool optFullscreen = true;
        static bool isDockspaceOpen = true;
        static bool optPadding = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (optFullscreen) {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 1);
        ImGui::Begin("DockSpace Demo", &isDockspaceOpen, window_flags);

        //ImGui::GetIO().DisplayFramebufferScale.x = WinData.xScale;
        //ImGui::GetIO().DisplayFramebufferScale.y = WinData.yScale;

        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
            ImGuiID dockspace_id = ImGui::GetID("MyDockspace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        ImGuiStyle& style = ImGui::GetStyle();
        style.WindowMenuButtonPosition = 2;
    }
    void EndDockspace() {
        ImGui::End();
        ImGui::PopStyleVar();
    }
private:
    ImGuiMenuPanel menuPanel;
    ImGuiDebugPanel debugPanel;
    ImGuiSignalsPanel signalsPanel;
    ImGuiViewportPanel viewportPanel;
    ImGuiPropertiesPanel propertiesPanel;
    ImGuiPreferencesPanel preferencesPanel;
    ImGuiControlsPanelBar controlsPanel;
    ImGuiScriptEditorPanel scriptEditorPanel;
    ImGuiSceneHeirarchyPanel sceneHeirarchyPanel;
    ImGuiFileManagerPanel fileManagerPanel;
    ImGuiResourcesPanel resourcesPanel;
    ImGuiLogPanel logPanel;
};
}
