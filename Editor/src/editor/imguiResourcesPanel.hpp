#pragma once
#include "core/corepch.h"
#include "editorState.h"
#include "imgui.h"
#include "util/resourceManager.h"

namespace Firefly {
struct ImGuiResourcesPanel {
    void Draw() {
        ImGui::Begin("Resources");
        if (ImGui::TreeNode("Editor")) {
            if (ImGui::TreeNode("Textures")) {
                for (const auto& t : ResourceManager::Get().uEngineTextures) {
                    if (ImGui::Selectable(t.second.get()->tag.c_str())){
                        LOG_INFO("Selected EngineTexture");
                        EditorState::Get().selectionId = t.second.get()->tag;
                        EditorState::Get().selectionType = SelectionType::ENGINE_TEXTURE;
                    }
                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Texture Atlases")) {
                for (const auto& ta : ResourceManager::Get().uEngineTextureAtlases) {
                    if (ImGui::Selectable(ta.second.get()->tag.c_str())){
                        LOG_INFO("Selected EngineTextureAtlas");
                        EditorState::Get().selectionId = ta.second.get()->tag;
                        EditorState::Get().selectionType = SelectionType::ENGINE_TEXTURE_ATLAS;
                    }
                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Shaders")) {
                for (const auto& s : ResourceManager::Get().uEngineShaders) {
                    if (ImGui::Selectable(s.second.get()->tag.c_str())) {
                        LOG_INFO("Selected EngineTextureAtlas");
                        EditorState::Get().selectionId = s.second.get()->tag;
                        EditorState::Get().selectionType = SelectionType::ENGINE_SHADER;
                    }
                }
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Project")) {
            if (ImGui::TreeNode("Textures")) {
                for (const auto& t : ResourceManager::Get().uTextures) {
                    if (ImGui::Selectable(t.second.get()->tag.c_str())) {
                        EditorState::Get().selectionId = t.second.get()->tag;
                        EditorState::Get().selectionType = SelectionType::TEXTURE;
                    }
                }

                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Texture Atlases")) {
                for (const auto& ta : ResourceManager::Get().uTextureAtlases) {
                    if (ImGui::Selectable(ta.second.get()->tag.c_str())) {
                        EditorState::Get().selectionId = ta.second.get()->tag;
                        EditorState::Get().selectionType = SelectionType::TEXTURE_ATLAS;
                    }
                }

                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Shaders")) {
                for (const auto& s : ResourceManager::Get().uShaders) {
                    if (ImGui::Selectable(s.second.get()->tag.c_str())) {
                        EditorState::Get().selectionId = s.second.get()->tag;
                        EditorState::Get().selectionType = SelectionType::SHADER;
                    }
                }
                
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        ImGui::End();
    }
};
}
