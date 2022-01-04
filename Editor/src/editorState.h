#pragma once
#include "core/corepch.h"
#include "core/serialization/json-serializable.h"
#include "core/engine/scene.h"
#include "renderer/framebuffer.h"
#include "core/engine/engineData.h"
#include <string>
#include <filesystem>
#include <fstream>

namespace Firefly {
struct Project : JsonSerializable {
    std::filesystem::path rootPath = "";
    std::filesystem::path openPath = "";
    bool savedToDisk = false;

    void SaveProject() {
        if (savedToDisk) {
            //SAVE
            //overwrite data in project dir
        }
        else {
            //NEW
            //create and intitialize the project dir
        }
    }

    bool AttemptOpenProject(const char* path) {
        if (Exists(path)) {
            rootPath = path;
            openPath = path;
            LOG_INFO("Opened project");
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
        fs.close();
        savedToDisk = true;
        return status;
    }

    bool Exists(const char* filepath) {
        return std::filesystem::exists(filepath);
    }

    void Serialize(json& value) override {
        value["open-project"]["root-path"] = rootPath;
        value["open-project"]["open-path"] = openPath;
        LOG_DEBUG("Serialized Project");
    }
    
    void Deserialize(json& value) override {
        rootPath = value["open-project"]["root-path"];
        openPath = value["open-project"]["open-path"];
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
        CurrentProject().Deserialize(root);
        LOG_DEBUG("End EditorState Deserialization -> Successful");
    }
    
private:
    Project currentProject;
    Scene currentScene;
    std::string selectionId;
    SelectionType selectionType;
    FrameBuffer viewportFramebuffer;
   
    friend class ImGuiResourcesPanel;
    friend class ImGuiSceneHeirarchyPanel;
    friend class ImGuiPropertiesPanel;
    friend class ImGuiViewportPanel;
};
}
