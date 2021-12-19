#pragma once
#include <string>
#include <filesystem>
#include "../serializer/serializable.h"

namespace Firefly {
enum class SelectionType {
    NONE, SIGNAL, GAMEOBJECT, TEXTURE, TEXTURE_ATLAS, SHADER, ENGINE_TEXTURE, ENGINE_TEXTURE_ATLAS, ENGINE_SHADER
};

//stores the user's preferences
struct EnginePreferences : public Serializable<EnginePreferences> {
    bool isResourcePanelEnabled = true;
    bool isSignalPanelEnabled = true;
    bool isFileManagerPanelEnabled = true;
    bool isRegistryPanelEnabled = true;
    bool isViewportPanelEnabled = true;
    bool isConsolePanelEnabled = true;
    bool isStatPanelEnabled = true;
    bool isPropertiesPanelEnabled = true;
    bool isScriptEditorPanelEnabled = true;
    bool isSceneHeirarchyPanelEnabled = true;
    bool isDemoWindowEnabled = false;

    void Serialize(const std::string& location) override {
        Serializer::SerializeBin<EnginePreferences>(location, *this);
        LOG_DEBUG("Serialized EnginePreferences {}", location);
    }

    EnginePreferences& Deserialize(const std::string& location) override {
        Serializer::DeSerializeBin<EnginePreferences>(location, *this);
        return *this;
    }
};

//stores the last state of the engine
struct EngineState : public Serializable<EngineState> {
    std::string openProject = ""; //the path of the last project that was open

    void Serialize(const std::string& location) override {
        Serializer::SerializeBin<EngineState>(location, *this);
        LOG_DEBUG("Serialized EngineState {}", location);
    }

    EngineState& Deserialize(const std::string& location) override {
        Serializer::DeSerializeBin<EngineState>(location, *this);
        return *this;
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

    static void SetSelected(SelectionType type, std::string id) {
        Get().selectionType = type;
        Get().selectionId = id;
    }

    static void Serialize() {
        LOG_INFO("Serializing engine data");
        Get().state.Serialize("res/engine_files/engine_state.bin");
        Get().preferences.Serialize("res/engine_files/engine_pref.bin");
    }

    static void Deserialize() {
        LOG_INFO("Deserializing engine data");
        Get().state.Deserialize("res/engine_files/engine_state.bin");
        Get().preferences.Deserialize("res/engine_files/engine_pref.bin");

        //down here we can initialize everything
        Get().rootDir = Get().state.openProject;
        Get().currentDir = Get().state.openProject;
    }

private:
    std::filesystem::path rootDir = "", currentDir = "";

private:
    SelectionType selectionType;
    std::string selectionId;

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
};
}
