#pragma once
#include "core/corepch.h"
#include "editorState.h"
#include "glad/glad.h"
#include "imgui.h"
#include "window/windowData.h"
#include "window/inputData.h"
#include "util/resourceManager.h"
#include "renderer/renderer2D_v2.h"

#include "ImGuizmo/ImGuizmo.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"

namespace Firefly {
struct ImGuiViewportPanel {
    ImVec2 lastViewportSize;

    ImGuiViewportPanel() {
        Renderer2D_V2::Init();
        EditorState::Get().viewportFramebuffer.Resize(1280, 720);
        LOG_DEBUG("Init viewport panel");
    }

    ~ImGuiViewportPanel() {
        Renderer2D_V2::Shutdown();
    }

    void Draw() {
        //test framebuffer
        FrameBuffer& fb = EditorState::Get().viewportFramebuffer;
        Scene* scene = EditorState::CurrentScene();
        scene->Draw(fb);
        scene->SetClearColor(EditorState::Get().clearColor);

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
        ImGui::Image((void*)(intptr_t) texId, viewportSize);//, {0, 1}, {1, 0});

        //Draw transformation options
        unsigned int iconTexId = ResourceManager::GetEngineResource<Texture>("move_icon")->textureHandle;
        ImGui::SetCursorPos({20,20});
        if (ImGui::ImageButton((void*)(intptr_t)iconTexId, {32, 32}, {0, 1}, {1, 0})) {
            EditorState::Get().currentImGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
        } ImGui::SameLine();

        iconTexId = ResourceManager::GetEngineResource<Texture>("rotate_icon")->textureHandle;
        if (ImGui::ImageButton((void*)(intptr_t)iconTexId, {32, 32}, {0, 1}, {1, 0})) {
            EditorState::Get().currentImGuizmoOperation = ImGuizmo::OPERATION::ROTATE;
        } ImGui::SameLine();

        iconTexId = ResourceManager::GetEngineResource<Texture>("scale_icon")->textureHandle;
        if (ImGui::ImageButton((void*)(intptr_t)iconTexId, {32, 32}, {0, 1}, {1, 0})) {
            EditorState::Get().currentImGuizmoOperation = ImGuizmo::OPERATION::SCALE;
        } ImGui::SameLine();
  
        DrawGizmos(scene);

        ImGui::End();
        ImGui::PopStyleVar();
    }

    void DrawGizmos(Scene* scene) {
        //Draw gizmos
        if (EditorState::Get().selectionType == SelectionType::ENTITY) {
            Entity* e = scene->FindEntity(EditorState::Get().selectionId);
            if (e) {
                ImGuizmo::SetOrthographic(true);
                ImGuizmo::SetDrawlist();

                ImGuiIO& io = ImGui::GetIO();
                float windowWidth = (float)ImGui::GetWindowWidth();
                float windowHeight = (float)ImGui::GetWindowHeight();
            
                //ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);
                ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

                const auto& cameraProj = EditorState::CurrentScene()->Camera().GetProj();
                auto cameraView = glm::inverse(EditorState::CurrentScene()->Camera().GetView());
                Transform& t = e->GetComponent<Transform>();
                glm::mat4 transform = t.transform;

                glm::vec3 translation;
                glm::vec3 scale;
                glm::vec3 skew;
                glm::vec4 perspective;
                glm::quat rotation;

                switch (EditorState::Get().currentImGuizmoOperation) {
                    case ImGuizmo::OPERATION::TRANSLATE:
                        {
                        ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProj),
                            ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::MODE::LOCAL, glm::value_ptr(transform));
                        break;
                        }
                    case ImGuizmo::OPERATION::ROTATE:
                        {

                        break;
                        }
                    case ImGuizmo::OPERATION::SCALE:
                        {

                        break;
                        }
                }
                if (ImGuizmo::IsUsing()) {
                    glm::decompose(transform, scale, rotation, translation, skew, perspective);
                    LOG_DEBUG("{} {}", translation.x, translation.y);
                    t.position = translation;
                    t.scale = scale;
                }
            }
        }

    }
};
}
