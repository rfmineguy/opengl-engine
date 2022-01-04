#pragma once
#include "core/corepch.h"
#include "imgui.h"

struct ImGuiLogPanel {
    bool showWarnings, showInfo, showDebug, showError, showCritical;
    ImGuiLogPanel() {
        showInfo = true;
        showWarnings = true;
        showDebug = true;
        showError = true;
        showCritical = true;
    }
    void Draw() {
        ImGui::Begin("Log");
        if (ImGui::BeginPopup("Options")) {
            ImGui::Checkbox("Info", &showInfo);
            ImGui::Checkbox("Debug", &showDebug);
            ImGui::Checkbox("Warnings", &showWarnings);
            ImGui::Checkbox("Error", &showError);
            ImGui::Checkbox("Critical", &showCritical);
            ImGui::EndPopup(); 
        }
        if (ImGui::Button("Options"))
            ImGui::OpenPopup("Options");

        ImGui::End();
    }
};
