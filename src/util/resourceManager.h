#pragma once

#include "../corepch.h"
#include "../render_data/texture.h"
#include "../render_data/textureAtlas.h"
#include "../render_data/shader.h"

//SINGLETON CLASS
class ResourceManager {
public:
    static ResourceManager& Get() {
        static ResourceManager resourceManager;
        return resourceManager;
    }
    static void LoadTexture(std::string name, std::string path) {
        Get().LoadTextureImpl(name, path);
    }
    static void LoadTextureAtlas(std::string name, std::string path) {
        Get().LoadTextureAtlasImpl(name, path);
    }
    static void LoadShader(std::string name, std::string path) {
        Get().LoadShaderImpl(name, path);
    }
    static Texture* GetTexture(std::string name) {
        return Get().GetTextureImpl(name);
    }
    static TextureAtlas* GetTextureAtlas(std::string name) {
        return Get().GetTextureAtlasImpl(name);
    }
    static Shader* GetShader(std::string name) {
        return Get().GetShaderImpl(name);
    }
    static void PrintContents() {
        Get().PrintContentsImpl();
    }
    static void Init() {
        Get().InitImpl();
    }
    static void Cleanup() {
        Get().CleanupImpl();
    }
private:
    void LoadShaderImpl(std::string name, std::string path) {
        LOG_INFO("ResourceManager::Loading Shader {0}", name);
        if (uShaders.find(name) != uShaders.end()) {
            LOG_WARN("ResourceManager::Shader Already Loaded {0}", name);
            return;
        }
        uShaders.emplace(name, std::make_unique<Shader>(path));
        LOG_INFO("ResourceManager::Loaded Shader - {0} at {1}", name, path);
    }
    
    void LoadTextureImpl(std::string name, std::string path) {
        LOG_INFO("ResourceManager::Loading texture {}", name);
         if (uTextures.find(name) != uTextures.end()) {
             LOG_ERROR("ResourceManager:::Texture already loaded");
             return;
         }
         uTextures.emplace(name, std::make_unique<Texture>(name));
         LOG_INFO("ResourceManager::Loaded texture {0} at {1}", name, path);
    }
    
    void LoadTextureAtlasImpl(std::string name, std::string path) {
        LOG_INFO("ResourceManager::Loading TextureAtlas {0}", name);
        if (uTextureAtlases.find(name) != uTextureAtlases.end()) {
            LOG_WARN("ResourceManager::TextureAtlas Already Loaded {0}", name);
            return;
        }
        uTextureAtlases.emplace(name, std::make_unique<TextureAtlas>(path));
        LOG_INFO("ResourceManager::Loaded TextureAtlas - {0} at {1}", name, path);
    }
    
    Texture* GetTextureImpl(std::string name) {
        if (uTextures.find(name) == uTextures.end()) {
            LOG_ERROR("ResourceManager::Texture not loaded. {0}", name);
            return nullptr;
        }
        return uTextures.at(name).get();
    }

    TextureAtlas* GetTextureAtlasImpl(std::string name) {
        if (uTextureAtlases.find(name) == uTextureAtlases.end()) {
            LOG_ERROR("ResourceManager::TextureAtlas not loaded - {0}", name);
            return nullptr;
        }
        return uTextureAtlases.at(name).get();
    }

    Shader* GetShaderImpl(std::string name) {
        if (uShaders.find(name) == uShaders.end()) {
            LOG_ERROR("ResourceManager::Shader not loaded. {0}", name);
            return nullptr; 
        }
        return uShaders.at(name).get();
    }
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
    }
    void InitImpl() {
        LOG_DEBUG("Initializing resource manager");
    }
    void CleanupImpl(){ 
        LOG_DEBUG("Cleaning up loaded resources");
    }
private:
    std::unordered_map<std::string, std::unique_ptr<Texture>> uTextures;    //https://duckduckgo.com/
    std::unordered_map<std::string, std::unique_ptr<TextureAtlas>> uTextureAtlases;
    std::unordered_map<std::string, std::unique_ptr<Shader>> uShaders;


friend class ImGuiLayer;
};
 
// (id, filename)
//ResourceManager::LoadTextureAtlas("spritesheet","atlas_test")
//ResourceManager::GetTexture("player");
//ResourceManager::GetShader("experimental");
