#pragma once
#include "core/corepch.h"
#include "imgui.h"
#include "util/resourceManager.h"

namespace Firefly {
struct ImGuiResourcesPanel {
    void Draw() {
        ImGui::Begin("Resources");
        if (ImGui::TreeNode("Editor")) {
            if (ImGui::TreeNode("Textures")) {
                for (const auto& t : ResourceManager::Get().uEngineTextures) {
                    if (ImGui::Selectable(t.second.get()->tag.c_str()))
                        EngineData::SetSelected(SelectionType::ENGINE_TEXTURE, t.second.get()->tag);
                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Texture Atlases")) {
                for (const auto& ta : ResourceManager::Get().uEngineTextureAtlases) {
                    if (ImGui::Selectable(ta.second.get()->tag.c_str()))
                        EngineData::SetSelected(SelectionType::ENGINE_TEXTURE_ATLAS, ta.second.get()->tag);
                }
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Shaders")) {
                for (const auto& s : ResourceManager::Get().uEngineShaders) {
                    if (ImGui::Selectable(s.second.get()->tag.c_str()))
                        EngineData::SetSelected(SelectionType::ENGINE_SHADER, s.second.get()->tag);
                }
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("Project")) {
            if (ImGui::TreeNode("Textures")) {
                for (const auto& t : ResourceManager::Get().uTextures) {
                    if (ImGui::Selectable(t.second.get()->tag.c_str()))
                        EngineData::SetSelected(SelectionType::TEXTURE, t.second.get()->tag);
                }

                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Texture Atlases")) {
                for (const auto& ta : ResourceManager::Get().uTextureAtlases) {
                    if (ImGui::Selectable(ta.second.get()->tag.c_str()))
                        EngineData::SetSelected(SelectionType::TEXTURE_ATLAS, ta.second.get()->tag);
                }

                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Shaders")) {
                for (const auto& s : ResourceManager::Get().uShaders) {
                    if (ImGui::Selectable(s.second.get()->tag.c_str()))
                        EngineData::SetSelected(SelectionType::SHADER, s.second.get()->tag);
                }
                
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
        ImGui::End();
    }
};
}
