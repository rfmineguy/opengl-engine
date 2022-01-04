#pragma once
#include "core/corepch.h"
#include "editorState.h"
#include "core/entity/entity.h"

namespace Firefly {
struct ImGuiSceneHeirarchyPanel {
    void Draw() {
        ImGui::Begin("Scene Heirarchy");
        Scene* scene = EditorState::CurrentScene();
        if (ImGui::CollapsingHeader("Entities")) {
            DrawHeirarchy(scene->root.get());
        }
        ImGui::End();
    }

    void DrawHeirarchy(Entity* entity) {
        Scene* scene = EditorState::CurrentScene();
        ImGuiTreeNodeFlags flags = (EditorState::Get().selectionId == entity->GetComponent<Identifier>().id ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        flags |= ImGuiTreeNodeFlags_SpanAvailWidth;
        auto& id = entity->GetComponent<Identifier>().id;
        
        if (DrawNode(entity, id)) {
            for (auto& id : entity->GetChildren()) {
                Entity* e = scene->FindEntity(id);
                if (e->GetParent() == entity->GetComponent<Identifier>().id) {
                    DrawHeirarchy(e);
                }
            }
            ImGui::TreePop();
        }
    }

    bool DrawNode(Entity* entity, const std::string& id) {
        ImGuiTreeNodeFlags flags = (EditorState::Get().selectionId == id ? ImGuiTreeNodeFlags_Selected : 0) | ImGuiTreeNodeFlags_OpenOnArrow;
        bool opened = ImGui::TreeNodeEx(id.c_str(), flags);
        if (ImGui::IsItemClicked()) {
            LOG_DEBUG("Clicked {}", id.c_str());
            if (id != "root") {
                EditorState::Get().selectionId = id;
                EditorState::Get().selectionType = SelectionType::ENTITY;
            }
        }
        return opened;
    }
};
}
