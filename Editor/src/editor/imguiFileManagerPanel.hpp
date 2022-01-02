#pragma once
#include "core/corepch.h"
#include "core/engine/engineData.h"
#include "imgui.h"

using namespace Firefly;
struct ImGuiFileManagerPanel {
    void Draw() {
        ImGui::Begin("File Manager");
        
        if (EngineData::Get().state.openProjectRoot.empty()) {
            float w = ImGui::GetWindowWidth();
            float h = ImGui::GetWindowHeight();
            ImGui::SetCursorPos({w/2 - 20, h/2});
            ImGui::Text("No project directory selected");
            ImGui::End();
            return;
        }
        if (EngineData::Get().state.currentDir != EngineData::Get().state.openProjectRoot) {
            if (ImGui::Button("<-")) {
                EngineData::Get().state.currentDir = EngineData::Get().state.currentDir.parent_path();
            }
        }

        const int ITEM_SPACING = 16;
        const int ITEM_SIZE = 128;
        const int COLUMNS_WIDE = ImGui::GetContentRegionAvailWidth() / ITEM_SIZE;
        ImGui::BeginTable("File Manager", COLUMNS_WIDE);
        ImGui::TableNextColumn();

        ImGui::EndTable();
        ImGui::End();
    }
};
