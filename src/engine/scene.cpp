#include "scene.h"

#include "../gameobject/entity.h"
#include "../components/components.h"
//#include "../renderer/renderer2D.h"

namespace Firefly {

Scene::Scene() {
    root = std::make_unique<Entity>(this);
}

Scene::~Scene() {

}

void Scene::Draw() {
    frameBuffer.Bind();
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    frameBuffer.Unbind();
}

void Scene::Update(float dt) {
    cam.Movement();
}

void Scene::CreateEntity(const std::string& id) {
    if (uEntities.count(id) == 0) {
        uEntities.emplace(id, std::make_unique<Entity>(this));
        Entity* e = FindEntity(id);
        e->AddComponent<Transform>(0, 0, 32, 32, 0);
        e->AddComponent<Identifier>(id, id);
        e->AddComponent<SpriteRenderer>();
        return;
    }
    LOG_WARN("Entity with id {} already exists", id.c_str());
}

Entity* Scene::FindEntity(const std::string& id) {
    if (uEntities.find(id) != uEntities.end()) {
        return uEntities.at(id).get();
    }
    return nullptr;
}

bool Scene::DestroyEntity(const std::string& id) {
    //UNIMPLEMENTED
    return false;
}
}
