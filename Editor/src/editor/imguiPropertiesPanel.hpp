#pragma once
#include "core/corepch.h"
#include "core/engine/engineData.h"
#include "util/resourceManager.h"

namespace Firefly {
struct ImGuiPropertiesPanel {
    void Draw() {
        ImGui::Begin("Properties");
        SelectionType& type = EngineData::Get().selectionType;//SelectedEntity();
        std::string& id = EngineData::Get().selectionId;

        //NOTHING SELECTED
        if (type == SelectionType::NONE) {
            ImGui::End();
            return;
        }

        if (type == SelectionType::ENTITY) {}
        else if (type == SelectionType::SIGNAL) {}
        else if (type == SelectionType::TEXTURE) {
            DrawTexture(id, false);
        }
        else if (type == SelectionType::TEXTURE_ATLAS) {
            DrawTextureAtlas(id, false);
        }
        else if (type == SelectionType::SHADER) {}
        else if (type == SelectionType::ENGINE_TEXTURE) {
            DrawTexture(id, true);
        }
        else if (type == SelectionType::ENGINE_TEXTURE_ATLAS) {
            DrawTextureAtlas(id, true);
        }
        else if (type == SelectionType::ENGINE_SHADER) {}
        ImGui::End();
    }

    void DrawTexture(const std::string& name, bool isEngine) {
        ImGui::Text("Texture");
        Texture* t = isEngine ? 
            ResourceManager::GetEngineResource<Texture>(name) :
            ResourceManager::GetProjectResource<Texture>(name);
        if (t) {
            ImGui::Image((void*)(intptr_t) t->textureHandle, ImVec2{64, 64}, ImVec2{0, 1}, ImVec2{1, 0});
        }
    }
    void DrawTextureAtlas(const std::string& name, bool isEngine) {
        ImGui::Text("TextureAtlas");
        TextureAtlas* ta = isEngine ?
            ResourceManager::GetEngineResource<TextureAtlas>(name) :
            ResourceManager::GetProjectResource<TextureAtlas>(name);
        if (ta) {
            ImGui::Image((void*)(intptr_t) ta->textureHandle, ImVec2{64, 64}, ImVec2{0, 1}, ImVec2{1, 0});
        }
    }
};
}
