#pragma once
#include "core/corepch.h"
#include "util/resourceManager.h"
#include "editorState.h"
#include "imgui.h"

using namespace Firefly;
struct ImGuiFileManagerPanel {
    void Draw() {
        ImGui::Begin("File Manager");
        
        if (EditorState::CurrentProject().rootPath.empty()) {
            float w = ImGui::GetWindowWidth();
            float h = ImGui::GetWindowHeight();
            ImGui::SetCursorPos({w/2 - 20, h/2});
            LOG_DEBUG("Root path empty");
            ImGui::Text("No project directory selected");
            ImGui::End();
            return;
        }
        
        if (EditorState::CurrentProject().openPath != EditorState::CurrentProject().rootPath) {
            if (ImGui::Button("<-")) {
                EditorState::CurrentProject().openPath = EditorState::CurrentProject().openPath.parent_path();
            }
        }

        const int ITEM_SPACING = 16;
        const int ITEM_SIZE = 128;
        const int COLUMNS_WIDE = ImGui::GetContentRegionAvailWidth() / ITEM_SIZE;

        int id = 0;
        if (ImGui::BeginTable("File Manager", COLUMNS_WIDE)) {
            ImGui::TableNextColumn();
            for (auto& p : std::filesystem::directory_iterator(EditorState::CurrentProject().openPath)) {
                const auto& path = p.path();
                auto relPath = std::filesystem::relative(path, EditorState::CurrentProject().openPath);
                std::string filenameStr = relPath.filename().string();

                if (filenameStr != ".DS_Store") {
                    ImGui::PushID(id);
                    Texture* folderTex = ResourceManager::GetEngineResource<Texture>("folder_icon");
                    Texture* fileTex = ResourceManager::GetEngineResource<Texture>("txt_file_icon");
                    if (p.is_directory()) {
                        if (ImGui::ImageButton((void*)(intptr_t) folderTex->textureHandle, ImVec2{128, 128}, ImVec2{0, 1}, ImVec2{1, 0})) {
                            LOG_DEBUG("Move directories");
                            EditorState::CurrentProject().openPath /= path.filename();
                        }
                    
                        ImGui::Text("%s", filenameStr.c_str());
                    }
                    else {
                        if (ImGui::ImageButton((void*)(intptr_t) fileTex->textureHandle, ImVec2{128, 128}, ImVec2{0, 1}, ImVec2{1, 0})) {
                            LOG_DEBUG("Open file (WIP)");
                        }
                    
                        ImGui::Text("%s", filenameStr.c_str());
                    }
                    ImGui::TableNextColumn();
                    ImGui::PopID();
                    id++;
                }
            }
            ImGui::EndTable();
        }
        
        ImGui::End();
    }
};
