#pragma once
#include "core/corepch.h"
#include "core/engine/scene.h"
#include "util/resourceManager.h"
#include "editorState.h"


namespace Firefly {
struct ImGuiControlsPanelBar {
    void Draw() {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, {0, 2});
        ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, {0, 0});
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0, 0, 0});
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{0.3f, 0.305f, 0.31f, 0.5f});
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{0.3f, 0.305f, 0.31f, 0.5f});

        ImGuiWindowFlags flags = 0;
        flags |= ImGuiWindowFlags_NoTitleBar;
        flags |= ImGuiWindowFlags_NoScrollbar;
        flags |= ImGuiWindowFlags_NoScrollWithMouse;
        flags |= ImGuiWindowFlags_NoResize;
        flags |= ImGuiWindowFlags_NoDecoration;

        ImGui::Begin("Controls", nullptr, flags);
        Scene* scene = EditorState::CurrentScene();
        Texture* icon = scene->State() == SceneState::STOPPED ?
            ResourceManager::GetEngineResource<Texture>("play_icon"):
            ResourceManager::GetEngineResource<Texture>("stop_icon");

        float size = ImGui::GetWindowHeight() - 4.0f;
        ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
        if (ImGui::ImageButton((void*)(intptr_t) icon->textureHandle, ImVec2 {20, 20})) {
            if (scene->State() == SceneState::STOPPED) {
                scene->Start();
            }
            else if (scene->State() == SceneState::PLAYING) {
                scene->Stop();
            }
        }
        ImGui::PopStyleColor(3);
        ImGui::PopStyleVar(2);
        ImGui::End();
    }
};
}
