#pragma once
#include "core/corepch.h"
#include "editorState.h"
#include "glad/glad.h"
#include "imgui.h"
#include "window/windowData.h"
#include "window/inputData.h"

namespace Firefly {
struct ImGuiViewportPanel {
    ImVec2 lastViewportSize;
    void Draw() {

        //test framebuffer
        FrameBuffer& fb = EditorState::Get().viewportFramebuffer;
        Scene* scene = EditorState::CurrentScene();
        scene->Draw(fb);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2 {0, 0});
        ImGui::Begin("Viewport");
        
        ImVec2 vMin = ImGui::GetWindowContentRegionMin();
        ImVec2 vMax = ImGui::GetWindowContentRegionMax();
        ImVec2 vOffset = ImGui::GetWindowPos();
        vMin.x += vOffset.x;    //topleft
        vMin.y += vOffset.y;    //
        vMax.x += vOffset.x;    //bottomright
        vMax.y += vOffset.y;    //

        ImVec2 mousePos = ImGui::GetMousePos(); //mousePos;
        Input.mouse.x = mousePos.x - vMin.x;    //subtract left edge from xCoord
        Input.mouse.y = mousePos.y - vMin.y;

        ImVec2 viewportSize = ImGui::GetContentRegionAvail();
        if (lastViewportSize.x != viewportSize.x || lastViewportSize.y != viewportSize.y) {
            fb.Resize(viewportSize.x, viewportSize.y);
            lastViewportSize = { viewportSize.x, viewportSize.y };

            EditorState::CurrentScene()->OnResize(viewportSize.x, viewportSize.y);
        }
        unsigned int texId = fb.GetColorAttachment();
        ImGui::Image((void*)(intptr_t) texId, viewportSize);

        ImGui::SetCursorPos({0, 0});
        ImGui::Text("The framebuffer seen here is done in ImGuiViewportPanel. This WILL change.");
        ImGui::End();
        ImGui::PopStyleVar();
    }
};
}
