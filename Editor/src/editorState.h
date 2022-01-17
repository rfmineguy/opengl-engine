#pragma once
#include "core/corepch.h"
#include "core/serialization/json-serializable.h"
#include "core/engine/scene.h"
#include "renderer/framebuffer.h"
#include "core/engine/engineData.h"
#include "util/resourceManager.h"
#include <string>
#include <filesystem>
#include <fstream>

namespace Firefly {
struct Project : JsonSerializable {
    std::filesystem::path rootPath = "";
    std::filesystem::path openPath = "";
    bool savedToDisk = false;
    bool isOpen = false;

    void SaveProject() {
    }

    bool AttemptOpenProject(std::filesystem::path path) {
        if (Exists(path)) {
            rootPath = path;
            openPath = path;

            LOG_INFO("Opening {}", path.c_str());
            std::fstream fs(path.append(".ffproj"));
            if (fs.fail()) {
                LOG_CRITICAL("Failed to open .ffproj");
            }
            json root;
            fs >> root;
            Deserialize(root);
            LOG_INFO("Opened project");
            isOpen = true;
            return true;
        }
        LOG_CRITICAL("Directory not a project");
        return false;
    }

    //Intialize the project directory with the basic folder and files
    // that define what a FireFly project is
    //   directories:
    //    - Atlases
    //    - Scripts
    //    - Scenes
    //    - Shaders
    //   files:
    //    - .ffproj
    bool Initialize(const char* path) {
        if (Exists(path)) {
            LOG_WARN("A project already exists at this path {}", path);
            return false;
        }
        rootPath = path;
        openPath = path;
        bool status = false;
        status = std::filesystem::create_directory(rootPath.parent_path().append("Atlases"));
        status = std::filesystem::create_directory(rootPath.parent_path().append("Scripts"));
        status = std::filesystem::create_directory(rootPath.parent_path().append("Scenes"));
        status = std::filesystem::create_directory(rootPath.parent_path().append("Shaders"));

        std::fstream fs(rootPath.parent_path().append(".ffproj"), std::ios::out);
        if (fs.fail()) {
            LOG_CRITICAL("Failed to create .ffproj");
            fs.close();
            return false;
        }
        json root;
        Serialize(root);
        fs << root;
        fs.close();
        savedToDisk = true;
        return status;
    }

    bool Exists(std::filesystem::path filepath) {
        return std::filesystem::exists(filepath);
    }

    void Serialize(json& value) override {
        value["open-project"]["root-path"] = rootPath;
        value["open-project"]["open-path"] = openPath;

        json loaded_resources = ResourceManager::Get().Serialize();
        value["loaded_resources"] = loaded_resources;
    }
    void Deserialize(json& value) override {
        LOG_DEBUG("Deserializer");
        rootPath = value["open-project"]["root-path"];
        openPath = value["open-project"]["open-path"];

        ResourceManager::Get().Deserialize(value["loaded_resources"], rootPath);
        LOG_DEBUG("Deserialized Project");
    }
};

class EditorState {
public:
    static EditorState& Get() {
        static EditorState state;
        return state;
    }

    static Project& CurrentProject() {
        return Get().currentProject;
    }

    static Scene* CurrentScene() {
        return &Get().currentScene;
    }

    /*
     * Serialize/Deserialize should be called when:
     *  the editor boots up -> Deserialize()
     *  the editor shuts down -> Serialize()
     */
    static void Serialize() {
        std::fstream fs("res/editor/editor-state.json", std::ios::out);
        json root;

        LOG_DEBUG("Begin EditorState Serialization");
        CurrentProject().Serialize(root);
        LOG_DEBUG("End EditorState Serialization");

        fs << root;
        fs.close();
    }

    static void Deserialize() {
        std::fstream fs("res/editor/editor-state.json", std::ios::in | std::ios::out);
        if (fs.fail()) {
            fs.close();
            Serialize();
        }
        fs.open("res/editor/editor-state.json", std::ios::in);

        json root;
        fs >> root;
        fs.close();
        
        LOG_DEBUG("Begin EditorState Deserialization");
        LOG_DEBUG("End EditorState Deserialization -> Successful");
    }
    
private:
    Project currentProject;
    int currentImGuizmoOperation;
    Scene currentScene;
    std::string selectionId;
    SelectionType selectionType;

    glm::vec4 clearColor;
    FrameBuffer viewportFramebuffer;
  
    friend class ImGuiPropertiesPanel;
    friend class ImGuiResourcesPanel;
    friend class ImGuiSceneHeirarchyPanel;
    friend class ImGuiDebugPanel;
    friend class ImGuiViewportPanel;
};
}
