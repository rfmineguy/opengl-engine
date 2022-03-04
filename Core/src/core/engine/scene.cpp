#include "scene.h"

#include "core/entity/entity.h"
#include "core/components/components.h"
//#include "renderer/renderer2D.h"
#include "renderer/renderer2D_v2.h"
#include "window/inputData.h"
#include "util/resourceManager.h"

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
    Draw(frameBuffer);
}

void Scene::Draw(FrameBuffer& fb) {
    Renderer2D_V2::BeginScene(Camera(), fb, clearColor);
    for (const auto& [name, entity] : uEntities) {
        OrthoCamera& primaryCam = Camera();
        Transform& t = entity.get()->GetComponent<Transform>();
        SpriteRenderer& sp = entity.get()->GetComponent<SpriteRenderer>();
        TextureAtlas* ta = ResourceManager::GetProjectResource<TextureAtlas>("spritesheet");
        Renderer2D_V2::DrawQuad(t, ta, "bigx");
    }
    Renderer2D_V2::EndScene();
}

void Scene::Update(float dt) {
    if (state == SceneState::PLAYING && focused) {
        OrthoCamera& primaryCam = Camera();
        primaryCam.Movement();
    }
}

void Scene::OnResize(int w, int h) {
    OrthoCamera& primaryCam = Camera();
    frameBuffer.Resize(w, h);
    primaryCam.UpdateProj(w, h);
    glViewport(0, 0, w, h);
}

void Scene::Start() {
    state = SceneState::PLAYING;
}

void Scene::Stop() {
    state = SceneState::STOPPED;
}

Entity* Scene::CreateEntity(const std::string& id) {
    if (uEntities.count(id) == 0) {
        uEntities.emplace(id, std::make_unique<Entity>(this, id));
    }
    Entity* e = FindEntity(id);
    e->AddComponent<Transform>(0, 0, 32, 32, 0);
    e->AddComponent<Identifier>(id, id);
    e->AddComponent<SpriteRenderer>();
    e->AddComponent<Renderable>("spritesheet", "bigx");
    e->AddComponent<Relationship>(false, false, 0, "root");
    root->AddChild(e);
    return e;
}

Entity* Scene::FindEntity(const std::string& id) {
    if (uEntities.find(id) != uEntities.end()) {
        return uEntities.at(id).get();
    }
    return nullptr;
}

Entity* Scene::FindPrimaryCamera() {
    for (auto& e: uEntities) {
        Entity* entity = e.second.get();
        if (entity->HasComponent<OrthoCameraTest>()) {
            if (entity->GetComponent<Identifier>().id.find("cam") != std::string::npos) {
                return entity;
            }
        }
    }
    LOG_WARN("No primary camera found");
    return nullptr;
}

bool Scene::DestroyEntity(const std::string& id) {
    return uEntities.erase(id);
}
}
