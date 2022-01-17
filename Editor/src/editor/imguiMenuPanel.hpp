#pragma once
#include "core/corepch.h"
#include "imgui.h"
#include "window/windowData.h"
#include "editorState.h"
#include <nfd.h>

/*
 * This library does not explicitly dispatch calls to the UI thread. 
 * This may lead to crashes if you call functions from other threads when
 * the platform does not support it (e.g. MacOS). Users are generally expected 
 * to call NFDe from an appropriate UI thread (i.e. the thread performing the UI
 * event loop).
 */
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
                if (!EditorState::CurrentProject().savedToDisk) 
                    ImGui::BeginDisabled();

                if (ImGui::MenuItem("Save Project WIP")) {
                    LOG_INFO("Project saving WIP");
                }
                ImGui::EndDisabled();

                if (ImGui::MenuItem("Save Project As")) {
                    nfdchar_t* path;
                    nfdresult_t result;
                    nfdfilteritem_t FilterItem[1] = { { "Project", "" } };
                    result = NFD_SaveDialog(&path, FilterItem, 1, NULL, "");
                    if (result == NFD_OKAY) {
                        LOG_INFO("Saved file (WIP) : {}", path);
                        if (EditorState::CurrentProject().Initialize(path)) {
                            LOG_DEBUG("Intialized project directory");
                        }
                        else {
                            LOG_CRITICAL("Failed to initialize project directory");
                        }
                        NFD_FreePath(path);
                    }
                }
                if (ImGui::MenuItem("Open Project"))  {
                    LOG_INFO("Open project");
                    nfdchar_t* path;
                    nfdresult_t result;
                    nfdfilteritem_t FilterItem[1] = { { "Project", "" } };
                    result = NFD_PickFolder(&path, NULL);
                    if (result == NFD_OKAY) {
                        EditorState::CurrentProject().AttemptOpenProject(path);
                    }
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
};
}
