#pragma once
#include <string>
#include <filesystem>

namespace Firefly {
enum class SelectionType {
    NONE, SIGNAL, GAMEOBJECT, TEXTURE, TEXTURE_ATLAS, SHADER, ENGINE_TEXTURE, ENGINE_TEXTURE_ATLAS, ENGINE_SHADER
};

class EngineData {
public:
    static EngineData& Get() {
        static EngineData engineData;
        return engineData;
    }

    static void SetSelected(SelectionType type, std::string id) {
        Get().selectionType = type;
        Get().selectionId = id;
    }

private:
    std::filesystem::path rootDir = "", currentDir = "";

private:
    SelectionType selectionType;
    std::string selectionId;

private:
    char scriptText[1024 * 16] = "";

//window enabled booleans
public:
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

friend class ImGuiLayer;
friend class ImGuiPropertiesPanel;
friend class ImGuiRegistryPanel;
friend class ImGuiScriptEditorPanel;
friend class ImGuiFileManagerPanel;
friend class ImGuiMenuPanel;
friend class ImGuiStatsPanel;
};
}
