#pragma once
#include <entt/entt.hpp>
#include <memory>
#include "../renderer/orthoCamera.h"
#include "../renderer/framebuffer.h"

namespace Firefly {

class Entity;

class Scene {
public:
    Scene();
    ~Scene();
    void Draw();
    void Update(float dt);
    void OnResize(int w, int h);

    void CreateEntity(const std::string& id);
    Entity* FindEntity(const std::string& id);
    bool DestroyEntity(const std::string& id);
    
private:
    entt::registry reg;
    OrthoCamera cam;
    FrameBuffer frameBuffer;

    std::unique_ptr<Entity> root;
    std::unordered_map<std::string, std::unique_ptr<Entity>> uEntities;
friend class Entity;
friend class Engine;
friend class ImGuiSceneHeirarchy;
};

}
