#pragma once
#include "core/corepch.h"
#include "core/engine/engineData.h"
#include "window/inputData.h"
#include "window/windowData.h"
#include "editorState.h"

namespace Firefly {
struct ImGuiDebugPanel {
    void Draw() {
        ImGui::Begin("Debug");

        if (ImGui::TreeNode("Viewport Data")) {
            ImGui::Text("Mouse Position {%0.4f %0.4f}", Input.mouse.x, Input.mouse.y);
            ImGui::Text("Viewport Size {%d %d}", Firefly::EngineData::CurrentScene().GetFrameBuffer().GetWidth(), Firefly::EngineData::CurrentScene().GetFrameBuffer().GetHeight());
            ImGui::Text("ImGui Scale {%0.4f %0.4f}", WinData.xScale, WinData.yScale);
            ImGui::TreePop();
        }
        ImGui::Dummy({0, 20});
        if (ImGui::TreeNode("File Structure Information")) {
            ImGui::Text("Project File{%s}", EditorState::CurrentProject().rootPath.c_str());
            ImGui::Text("Open Path{%s}", EditorState::CurrentProject().openPath.c_str());
            //ImGui::Text("Project Root {%s}", Firefly::EngineData::Get().state.openProjectRoot.c_str());           
            ImGui::TreePop();
        }
        ImGui::Dummy({0, 20});
        if (ImGui::TreeNode("Preferences")) {
            ImGui::Text("ResourcePanel: ");
            ImGui::TreePop();
        }
        ImGui::End();
    }
};
}
