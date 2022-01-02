#pragma once
#include "core/corepch.h"
#include "imgui.h"

struct ImGuiSignalsPanel {
    void Draw() {
        ImGui::Begin("Signals");
        if (ImGui::CollapsingHeader("Signals")) {
            ImGui::Text("Signals WIP");
        }
        ImGui::End();
    }
};
