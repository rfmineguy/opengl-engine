#pragma once
#include "core/corepch.h"
#include "imgui.h"
#include "window/windowData.h"
#include "editorState.h"
#include <nfd.h>

namespace Firefly {
struct ImGuiMenuPanel {
    ImGuiMenuPanel() {
        NFD_Init();
    }

    ~ImGuiMenuPanel() {
        NFD_Quit();
    }

    void Draw() {
        if(ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("New Project"))   {
                    LOG_INFO("Setting up new project");
                }
                if (ImGui::MenuItem("Save Project As")) {
                    nfdchar_t* path;
                    nfdresult_t result;
                    nfdfilteritem_t FilterItem[1] = { { "Project", "ffproject" } };
                    result = NFD_SaveDialog(&path, FilterItem, 1, NULL, "untitled");
                    //result = NFD_OpenDialog(&path, FilterItem, 2, NULL);
                    if (result == NFD_OKAY) {
                        LOG_INFO("Saved file (WIP) : {}", path);
                        NFD_FreePath(path);
                    }
                    else if (result == NFD_CANCEL) {
                        LOG_INFO("User pressed cancel.");
                    }
                    else {
                        LOG_ERROR("%s", NFD_GetError());
                    }
                }
                if (ImGui::MenuItem("Open Project"))  {
                    LOG_INFO("Open project");
                    nfdchar_t* path;
                    nfdresult_t result;

                }
                if (ImGui::MenuItem("New Scene"))   {
                    LOG_INFO("New scene");
                }
                if (ImGui::MenuItem("Save Scene"))  {}
                if (ImGui::MenuItem("Open Scene"))  {}
                if (ImGui::MenuItem("Close Scene")) {}
                if (ImGui::MenuItem("Open Recent")) {}
                if (ImGui::MenuItem("Quit"))        { WinData.shouldClose = true; }
                ImGui::EndMenu();
            }
            
            if (ImGui::BeginMenu("Edit")) {
                if (ImGui::MenuItem("Copy")) {}
                if (ImGui::MenuItem("Cut")) {}
                if (ImGui::MenuItem("Paste")) {}
                if (ImGui::MenuItem("Undo")) {}
                if (ImGui::MenuItem("Redo")) {}
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }
    }

    void HandleOpenFileDialog() {}
    void HandleSaveFileDialog() {}
};
}
