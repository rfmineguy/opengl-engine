#include "scene.h"

#include "../gameobject/entity.h"
#include "../components/components.h"
#include "../renderer/renderer2D.h"
#include "../window/inputData.h"

namespace Firefly {

Scene::Scene() {
    root = std::make_unique<Entity>(this, "root");
    root->AddComponent<Relationship>();
    root->GetComponent<Relationship>().isParent = true;
    root->GetComponent<Relationship>().level = 0;
    root->AddComponent<Identifier>("root", "root");
}

Scene::~Scene() {

}

void Scene::Draw() {
    frameBuffer.Bind();
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (const auto& entity : uEntities) {
        Renderer2D::Draw(*entity.second.get(), cam);
    }

    frameBuffer.Unbind();
}

void Scene::Update(float dt) {
    cam.Movement();
    glm::vec2 worldMouse = cam.ScreenToWorld(Input.mouse);
}

void Scene::OnResize(int w, int h) {
    frameBuffer.Resize(w, h);
}

void Scene::Start() {
    state = SceneState::PLAYING;
}

void Scene::Stop() {
    state = SceneState::STOPPED;
}

void Scene::CreateEntity(const std::string& id) {
    if (uEntities.count(id) == 0) {
        uEntities.emplace(id, std::make_unique<Entity>(this, id));
        Entity* e = FindEntity(id);
        e->AddComponent<Transform>(0, 0, 32, 32, 0);
        e->AddComponent<Identifier>(id, id);
        e->AddComponent<SpriteRenderer>();
        e->AddComponent<Renderable>("spritesheet", "bigx");
        e->AddComponent<Relationship>(false, false, 0, "root");
        root->AddChild(e);
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
