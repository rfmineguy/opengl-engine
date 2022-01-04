#pragma once
#include <entt/entt.hpp>
#include <memory>
#include "renderer/orthoCamera.h"
#include "renderer/framebuffer.h"

namespace Firefly {

class Entity;

enum class SceneState {
    PLAYING, STOPPED
};

class Scene {
public:
    Scene();
    ~Scene();
    void Draw();
    void Draw(FrameBuffer& fb);
    void Update(float dt);
    void OnResize(int w, int h);

    void Start();
    void Stop();

    Entity* CreateEntity(const std::string& id);
    Entity* FindEntity(const std::string& id);
    Entity* FindPrimaryCamera();
    bool DestroyEntity(const std::string& id);

    OrthoCamera& Camera() { return cam; }
    SceneState State() { return state; }
    FrameBuffer& GetFrameBuffer() { return frameBuffer; }
    int Size() { return uEntities.size(); }
    
private:
    SceneState state;
    bool focused = false;

    entt::registry reg;
    OrthoCamera cam;
    FrameBuffer frameBuffer;

    std::unique_ptr<Entity> root;
    std::unordered_map<std::string, std::unique_ptr<Entity>> uEntities;
friend class Entity;
friend class Engine;
friend class ImGuiSceneHeirarchy;
friend class ImGuiViewportPanel;
friend class ImGuiDebugPanel;
friend class ImGuiSceneHeirarchyPanel;
};

}
