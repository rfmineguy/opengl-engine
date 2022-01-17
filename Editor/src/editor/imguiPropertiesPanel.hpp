#pragma once
#include "core/corepch.h"
#include "core/engine/engineData.h"
#include "imgui.h"
#include "util/resourceManager.h"
#include "imgui/imgui_stdlib.h"

#include "editorState.h"
namespace Firefly {
struct ImGuiPropertiesPanel {
    const float DRAW_SIZE = 256;
    struct CallbackData {
        std::string* registryId;
        std::string* displayName;
    };
    struct PropertiesCallbacks {
        static int DisplayNameChanged(ImGuiInputTextCallbackData* data) {
            if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {
                LOG_WARN("Display name editing not functional");
                CallbackData* callbackdata = (CallbackData*)data->UserData;
            }
            return 0;
        }
    };
    void Draw() {
        ImGui::Begin("Properties");
        SelectionType& type = EditorState::Get().selectionType;//SelectedEntity();
        std::string& id = EditorState::Get().selectionId;

        //NOTHING SELECTED
        if (type == SelectionType::NONE) {
            ImGui::End();
            return;
        }

        if (type == SelectionType::ENTITY) {
            Entity* e = EditorState::CurrentScene()->FindEntity(id);

            DisplayComponents(e);
            AddComponentWigdet(e);
        }
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
    void DisplayComponents(Entity* entity) {
        if (entity->HasComponent<Identifier>()) {
            if (ImGui::TreeNode("Identifier")) {
                CallbackData data;
                data.registryId = &entity->GetComponent<Identifier>().id;
                data.displayName = &entity->GetComponent<Identifier>().displayName;

                ImGui::Text("ID: %s", data.registryId->c_str());
                ImGui::InputText("Display Name: ", &*data.displayName, ImGuiInputTextFlags_CallbackEdit, PropertiesCallbacks::DisplayNameChanged, (void*)&data);
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Relationship>()) {
            if (ImGui::TreeNode("Relationship")) {
                Relationship& r = entity->GetComponent<Relationship>();
                ImGui::Text("Parent : %s", r.parent.c_str());
                ImGui::Text("Level : %d", r.level);
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<OrthoCameraTest>()) {
            if (ImGui::TreeNode("OrthoCamera")) {
                OrthoCameraTest& camera = entity->GetComponent<OrthoCameraTest>();
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Transform>()) {
            if (ImGui::TreeNode("Transform")) {
                Transform& t = entity->GetComponent<Transform>();
                ImGui::DragFloat2("Position", &t.position.x);
                ImGui::DragFloat2("Scale", &t.scale.x);
                ImGui::DragFloat("Rotation", &t.rotation);
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Renderable>()) {
            if (ImGui::TreeNode("Renderable")) {
                CallbackData data;
                Renderable& r = entity->GetComponent<Renderable>();
                TextureAtlas* atlas = ResourceManager::GetProjectResource<TextureAtlas>(r.resourceId);
                ImGui::Image((void*)(intptr_t) atlas->textureHandle, ImVec2{64, 64}, ImVec2{0, 1}, ImVec2{1, 0});
                if (ImGui::BeginListBox("Subregions")) {
                    int id = 0;
                    for (auto& element : atlas->map) {
                        const bool is_selected = (r.atlasSubRegionName == element.first);
                        if (ImGui::Selectable(element.first.c_str(), is_selected)) {
                            LOG_DEBUG("Selected {}", element.first.c_str());
                            r.atlasSubRegionName = element.first;
                            //r.region = Renderer2D::Get().textureAtlas->GetRegion(element.first);
                        }

                        if (is_selected)
                            ImGui::SetItemDefaultFocus();

                        id++;
                    }
                    ImGui::EndListBox();
                }
                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<AnimatedRenderable>()) {
            if (ImGui::TreeNode("Animated Renderable")) {

                ImGui::TreePop();
            }
        }
        if (entity->HasComponent<Script>()) {
            if (ImGui::TreeNode("Script")) {
                Script& s = entity->GetComponent<Script>();
                ImGui::Text("%s", s.luaScriptPath.c_str());
            }
        }
        if (entity->HasComponent<SpriteRenderer>()) {
            if (ImGui::TreeNode("SpriteRenderer")) {
                SpriteRenderer& r = entity->GetComponent<SpriteRenderer>();
                ImGui::Text("Source Resource ID %s", r.texture->atlasName.c_str());
                ImGui::Text("AtlasSubRegionName %s", r.atlasSubRegionName.c_str());
                ImGui::TreePop();    
            }
        }
    }
    void AddComponentWigdet(Entity* entity) {
        if (ImGui::Button("Add Component")) {
            ImGui::OpenPopup("addcomponent-popup");
        }
        if (ImGui::IsPopupOpen("addcomponent-popup")) {
            if (!entity->HasComponent<Identifier>()) {
                entity->AddComponent<Identifier>("", "");
            }
            if (!entity->HasComponent<Transform>()) {
                entity->AddComponent<Transform>(0, 0, 32, 32, 0);
            }
            if (!entity->HasComponent<Renderable>()) {
                LOG_DEBUG("Adding renderable component isn't supported yet");
            }
            if (!entity->HasComponent<AnimatedRenderable>()) {
                LOG_DEBUG("Adding renderable component isn't supported yet");
            }
            if (!entity->HasComponent<Script>()) {
                entity->AddComponent<Script>("no script");
            }
            ImGui::EndPopup();
        }
    }
};
}
