#pragma once
#include <string>
#include <filesystem>
#include "../serializer/serializable.h"
#include "../serializer/json-serializable.h"
#include "scene.h"

namespace Firefly {
enum class SelectionType {
    NONE, ENTITY, SIGNAL, GAMEOBJECT, TEXTURE, TEXTURE_ATLAS, SHADER, ENGINE_TEXTURE, ENGINE_TEXTURE_ATLAS, ENGINE_SHADER
};

//stores the user's preferences
struct EnginePreferences : public JsonSerializable {
    bool isResourcePanelEnabled = true;
    bool isSignalPanelEnabled = true;
    bool isFileManagerPanelEnabled = true;
    bool isRegistryPanelEnabled = true;
    bool isViewportPanelEnabled = true;
    bool isStatPanelEnabled = true;
    bool isPropertiesPanelEnabled = true;
    bool isScriptEditorPanelEnabled = true;
    bool isSceneHeirarchyPanelEnabled = true;
    bool isControlsBarPanelEnabled = true;
    bool isPreferencesWindowEnabled = false;
    bool isDemoWindowEnabled = false;

    void Serialize(json& jValue) override {
        jValue["engine-prefs"]["isResourcePanelEnabled"]       = isResourcePanelEnabled;
        jValue["engine-prefs"]["isSignalPanelEnabled"]         = isSignalPanelEnabled;
        jValue["engine-prefs"]["isFileManagerPanelEnabled"]    = isFileManagerPanelEnabled;
        jValue["engine-prefs"]["isRegistryPanelEnabled"]       = isRegistryPanelEnabled;
        jValue["engine-prefs"]["isViewportPanelEnabled"]       = isViewportPanelEnabled;
        jValue["engine-prefs"]["isStatPanelEnabled"]           = isStatPanelEnabled;
        jValue["engine-prefs"]["isPropertiesPanelEnabled"]     = isPropertiesPanelEnabled;
        jValue["engine-prefs"]["isScriptEditorPanelEnabled"]   = isScriptEditorPanelEnabled;
        jValue["engine-prefs"]["isSceneHeirarchyPanelEnabled"] = isSceneHeirarchyPanelEnabled;
        jValue["engine-prefs"]["isControlsBarPanelEnabled"]    = isControlsBarPanelEnabled;
        jValue["engine-prefs"]["isPreferencesWindowEnabled"]   = isPreferencesWindowEnabled;
        jValue["engine-prefs"]["isDemoWindowEnabled"]          = isDemoWindowEnabled;
    }

    void Deserialize(json& jValue) override {
       isResourcePanelEnabled       = jValue["engine-prefs"]["isResourcePanelEnabled"]; 
       isSignalPanelEnabled         = jValue["engine-prefs"]["isSignalPanelEnabled"]; 
       isFileManagerPanelEnabled    = jValue["engine-prefs"]["isFileManagerPanelEnabled"]; 
       isRegistryPanelEnabled       = jValue["engine-prefs"]["isRegistryPanelEnabled"]; 
       isViewportPanelEnabled       = jValue["engine-prefs"]["isViewportPanelEnabled"]; 
       isStatPanelEnabled           = jValue["engine-prefs"]["isStatPanelEnabled"];
       isPropertiesPanelEnabled     = jValue["engine-prefs"]["isPropertiesPanelEnabled"]; 
       isSceneHeirarchyPanelEnabled = jValue["engine-prefs"]["isSceneHeirarchyPanelEnabled"];
       isControlsBarPanelEnabled    = jValue["engine-prefs"]["isControlsBarPanelEnabled"];
       isPreferencesWindowEnabled   = jValue["engine-prefs"]["isPreferencesWindowEnabled"];
       isDemoWindowEnabled          = jValue["engine-prefs"]["isDemoWindowEnabled"]; 
    }
};

//stores the last state of the engine
//can't serialize an `std::string` as binary
struct EngineState : public JsonSerializable {
    std::filesystem::path openProjectRoot = ""; //the path of the last project that was open
    std::filesystem::path currentDir = "";

    void Serialize(json& jValue) override {
        jValue["engine-state"]["open-project"] = openProjectRoot;//.root_path();
    }

    void Deserialize(json& jValue) override {
        std::string openProjPath = jValue["engine-state"]["open-project"];
        openProjectRoot = openProjPath; 
        currentDir = openProjectRoot;
    }
};

class EngineData {//: public Serializable<EngineData> {
public:
    static EngineData& Get() {
        static EngineData engineData;
        return engineData;
    }

    static EnginePreferences& Preferences() {
        return Get().preferences;
    }

    static EngineState& State() {
        return Get().state;
    }

    static Scene& CurrentScene() {
        return Get().currentScene;
    }

    static void SetSelected(SelectionType type, std::string id) {
        Get().selectionType = type;
        Get().selectionId = id;
    }

    static void Serialize() {
        LOG_INFO("Serializing engine data");
        std::fstream fs("res/engine_files/engine.json", std::ios::out);
        json root;
        Get().preferences.Serialize(root);
        Get().state.Serialize(root);
        fs << root;
        fs.close();
    }

    static void Deserialize() {
        LOG_INFO("Deserializing engine data");
        std::fstream fs("res/engine_files/engine.json", std::ios::in | std::ios::out);
        if (fs.fail()) {
            LOG_CRITICAL("Failed to open engine.json");
            Serialize();
            fs.close();
        }
        fs.open("res/engine_files/engine.json", std::ios::in);
        json root;
        fs >> root;
        fs.close();
        Get().state.Deserialize(root);
        Get().preferences.Deserialize(root);
    }

private:
    SelectionType selectionType;
    std::string selectionId;
    Scene currentScene;

private:
    char scriptText[1024 * 16] = "";

public:
    EnginePreferences preferences;
    EngineState state;

friend class ImGuiLayer;
friend class ImGuiPropertiesPanel;
friend class ImGuiRegistryPanel;
friend class ImGuiScriptEditorPanel;
friend class ImGuiFileManagerPanel;
friend class ImGuiMenuPanel;
friend class ImGuiStatsPanel;
friend class ImGuiSceneHeirarchy;
friend class Engine;
};
}
