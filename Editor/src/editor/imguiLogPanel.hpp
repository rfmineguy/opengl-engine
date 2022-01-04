#pragma once
#include "core/corepch.h"
#include "imgui.h"

namespace Firefly {
struct ImGuiLogPanel {
    bool showWarnings, showInfo, showDebug, showError, showCritical;
    
    ImGuiTextBuffer buf;
    ImGuiTextFilter filter;
    ImVector<int> lineOffsets;
    bool autoScroll;

    ImGuiLogPanel() {
        showInfo = true;
        showWarnings = true;
        showDebug = true;
        showError = true;
        showCritical = true;

        autoScroll = true;
    }
    
    void Clear() {
        buf.clear();
        lineOffsets.clear();
        lineOffsets.push_back(0);
    }

    void AddLog() {

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

        ImGui::SameLine();
        if (ImGui::Button("Log Tester")) {
            AddLog();
        }

        ImGui::End();
    }
};
}
