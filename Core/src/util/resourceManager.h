#pragma once

#include "core/corepch.h"
#include <typeinfo>
#include "renderer/texture.h"
#include "renderer/textureAtlas.h"
#include "renderer/shader.h"
#include "core/engine/engineData.h"
#include "core/engine/engine.h"

//SINGLETON CLASS
namespace Firefly {

class ResourceManager {
public:
    static ResourceManager& Get() {
        static ResourceManager resourceManager;
        return resourceManager;
    }
    static void PrintContents() {
        Get().PrintContentsImpl();
    }

    static void Cleanup() {
        Get().CleanupImpl();
    }

    template <typename T>
    static bool LoadProjectResource(const std::string& name, const std::string& path) {
        return Get().LoadProjectResourceImpl<T>(name, path);
    }

    template <typename T>
    static bool UnloadProjectResource(const std::string& name) {
        return Get().UnloadProjectResourceImpl<T>(name);
    }

    template <typename T>
    static T* GetProjectResource(const std::string& name) {
        return Get().GetProjectResourceImpl<T>(name);
    }

    template <typename T>
    static bool LoadEngineResource(const std::string& name, const std::string& path) {
        return Get().LoadEngineResourceImpl<T>(name, path);
    }

    template <typename T>
    static bool UnloadEngineResource(const std::string& name) {
        return Get().UnloadEngineResourceImpl<T>(name);
    }

    template <typename T>
    static T* GetEngineResource(const std::string& name) {   
        return Get().GetEngineResourceImpl<T>(name);
    }
private:
    template <typename T>
    bool LoadProjectResourceImpl(const std::string& name, const std::string& path) {
        bool status = false;
        std::string absPath = EngineData::Get().state.openProjectRoot;
        absPath += path;
        if (std::is_same<T, Texture>() && uTextures.count(name) == 0) {
            uTextures.emplace(name, std::make_unique<Texture>(name, absPath));
            status = true;
        }
        if (std::is_same<T, TextureAtlas>() && uTextureAtlases.count(name) == 0) {
            uTextureAtlases.emplace(name, std::make_unique<TextureAtlas>(name, absPath));
            status = true;
        }
        if (std::is_same<T, Shader>() && uShaders.count(name) == 0) {
            uShaders.emplace(name, std::make_unique<Shader>(name, absPath));
            status = true;
        }
        if (!status) {
            LOG_CRITICAL("Failed to load resource {}", name.c_str());
        }
        return status;
    }

    template <typename T>
    bool UnloadProjectResourceImpl(const std::string& name) {
        if (std::is_same<T, Texture>() && uTextures.count(name) == 1) {
            uTextures.erase(name);
            return true;
        }
        if (std::is_same<T, TextureAtlas>() && uTextureAtlases.count(name) == 1) {
            uTextureAtlases.erase(name);
            return true;
        }
        if (std::is_same<T, Shader>() && uShaders.count(name) == 1) {
            uShaders.erase(name);
            return true;
        }
        return false;
    }

    template <typename T>
    bool LoadEngineResourceImpl(const std::string& name, const std::string& path) {
        bool status = false;
        if (std::is_same<T, Texture>() && uEngineTextures.count(name) == 0) {
            uEngineTextures.emplace(name, std::make_unique<Texture>(name, path));
            status = true;
        }
        if (std::is_same<T, TextureAtlas>() && uEngineTextureAtlases.count(name) == 0) {
            uEngineTextureAtlases.emplace(name, std::make_unique<TextureAtlas>(name, path));
            status = true;
        }
        if (std::is_same<T, Shader>() && uEngineShaders.count(name) == 0) {
            uEngineShaders.emplace(name, std::make_unique<Shader>(name, path));
            status = true;
        }
        if (status == false) {
            LOG_CRITICAL("{} not supported by the resource manager", typeid(T).name());
        }
        return status;
    }

    template <typename T>
    bool UnloadEngineResourceImpl(const std::string& name) {
        if (std::is_same<T, Texture>() && uEngineTextures.count(name) == 1) {
            uEngineTextures.erase(name);
            return true;
        }
        if (std::is_same<T, TextureAtlas>() && uEngineTextureAtlases.count(name) == 1) {
            uEngineTextureAtlases.erase(name);
            return true;
        }
        if (std::is_same<T, Shader>() && uEngineShaders.count(name) == 1) {
            uEngineShaders.erase(name);
            return true;
        }
        return false;
    }

    template <typename T>
    T* GetProjectResourceImpl(const std::string& name) {
        if constexpr (std::is_same<T, Texture>::value) {
            if (uTextures.count(name) == 1) {
                return uTextures.at(name).get();
            }
        }
        if constexpr (std::is_same<T, TextureAtlas>::value) {
            if (uTextureAtlases.count(name) == 1) {
                return uTextureAtlases.at(name).get();
            }
        }
        if constexpr (std::is_same<T, Shader>::value) {
            if (uShaders.count(name) == 1) {
                return uShaders.at(name).get();
            }
        }
        LOG_CRITICAL("{} not loaded", name.c_str());
        return nullptr;
    }

    template <typename T>
    T* GetEngineResourceImpl(const std::string& name) {
        if constexpr(std::is_same<T, Texture>::value) {
            if (uEngineTextures.count(name) == 1) {
                return uEngineTextures.at(name).get();
            }
        }
        if constexpr(std::is_same<T, TextureAtlas>::value) {
            if (uEngineTextureAtlases.count(name) == 1) {
                return uEngineTextureAtlases.at(name).get();
            }
        }
        if constexpr(std::is_same<T, Shader>::value) { 
            if (uEngineShaders.count(name) == 1) {
                return uEngineShaders.at(name).get();
            }
        }
        LOG_CRITICAL("{} not loaded", name.c_str());
        return nullptr;
    }

private:
    void PrintContentsImpl() {
        LOG_DEBUG("*** PRINTING LOADED RESOURCES ***");

        LOG_DEBUG("\t===TEXTURES===");
        int count = 0;
        for (auto const& tex: uTextures) {
            count++;
            LOG_INFO("\t{0}\t {1} : {2}", count, tex.first, tex.second->tag);
        }
        count = 0;
        LOG_DEBUG("\t===TEXTURE ATLASES===");
        for (auto const& texAtlas: uTextureAtlases) {
            count++;
            LOG_INFO("\t{0}\t {1} : {2}", count, texAtlas.first, texAtlas.second->tag);
        }
        count = 0;
        LOG_DEBUG("\t===SHADERS===");
        for (auto const& shader: uShaders) {
            count++;
            LOG_INFO("\t{0}\t {1} : {2}", count, shader.first, shader.second->tag);
        }
        LOG_DEBUG("*** PRINTING LOADED RESOURCES ***");

        LOG_DEBUG("\t===ENGINE TEXTURES===");
        count = 0;
        for (auto const& tex: uEngineTextures) {
            count++;
            LOG_INFO("\t{0}\t {1} : {2}", count, tex.first, tex.second->tag);
        }
        count = 0;
        LOG_DEBUG("\t===ENGINE TEXTURE ATLASES===");
        for (auto const& texAtlas: uEngineTextureAtlases) {
            count++;
            LOG_INFO("\t{0}\t {1} : {2}", count, texAtlas.first, texAtlas.second->tag);
        }
        count = 0;
        LOG_DEBUG("\t===ENGINE SHADERS===");
        for (auto const& shader: uEngineShaders) {
            count++;
            LOG_INFO("\t{0}\t {1} : {2}", count, shader.first, shader.second->tag);
        }
    }

    json Serialize() {
        json resourcePool;
        int i = 0;
        for (auto &[key, value] : uTextures) {
            resourcePool[i]["key"] = key;
            resourcePool[i]["value"] = value.get()->path;
            resourcePool[i]["type"] = "tex";
            resourcePool[i]["is_editor"] = false;
            i++;
        }

        for (auto &[key, value] : uTextureAtlases) {
            resourcePool[i]["key"] = key;
            resourcePool[i]["value"] = value.get()->path;
            resourcePool[i]["type"] = "atlas";
            resourcePool[i]["is_editor"] = false;
            i++;
        }
            
        for (auto &[key, value] : uShaders) {
            resourcePool[i]["key"] = key;
            resourcePool[i]["value"] = value.get()->path;
            resourcePool[i]["type"] = "shader";
            resourcePool[i]["is_editor"] = false;
            i++;
        }

        return resourcePool;
    }

    void Deserialize(json& value, std::filesystem::path rootPath) {
        LOG_DEBUG("Deserializing resource json");
        
        for (auto &element : value) {
            std::string key = element["key"];
            std::string value = element["value"];
            std::string type = element["type"];
            bool isEditor = element["is_editor"];
        
            if (type == "tex") {
                LoadProjectResource<Texture>(key, rootPath / value);
                LOG_DEBUG("Loaded texture {}", key);
            }
            else if (type == "atlas") {
                LoadProjectResource<TextureAtlas>(key, rootPath / value);
                LOG_DEBUG("Loaded texture atlas {}", key);
            }
            else if (type == "shader") {
                LoadProjectResource<Shader>(key, rootPath / value);
                LOG_DEBUG("Loaded shader {}", key);
            }
        }
    }

    void CleanupImpl() {
        uTextures.clear();
        uTextureAtlases.clear();
        uShaders.clear();
        uEngineTextures.clear();
        uEngineTextureAtlases.clear();
        uEngineShaders.clear();
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> uTextures;    //https://duckduckgo.com/
    std::unordered_map<std::string, std::unique_ptr<TextureAtlas>> uTextureAtlases;
    std::unordered_map<std::string, std::unique_ptr<Shader>> uShaders;

    std::unordered_map<std::string, std::unique_ptr<Texture>> uEngineTextures;    //https://duckduckgo.com/
    std::unordered_map<std::string, std::unique_ptr<TextureAtlas>> uEngineTextureAtlases;
    std::unordered_map<std::string, std::unique_ptr<Shader>> uEngineShaders;

friend class ImGuiResourcesPanel;
friend class ImGuiFileManagerPanel;
friend class EditorState;
friend class Engine;
friend class Project;
};
}
