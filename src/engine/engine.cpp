#include "engine.h"
#include "../serializer/serializer.h"
#include <string>

namespace Firefly {
Engine::Engine() {
    Create();
}

Engine::~Engine() {
    Renderer2D::DeInit();
}

void Engine::Create() {
    //Load last opened project or none if no cached project was found

    EngineData::Deserialize();  //load saved engine data
    ResourceManager::LoadEngineResource<Texture>("folder_icon", "res/engine_files/file_browser/folder.png");
    ResourceManager::LoadEngineResource<Texture>("file_icon", "res/engine_files/file_browser/txt_file.png");
    ResourceManager::LoadEngineResource<Texture>("play_icon", "res/engine_files/controls/play.png");
    ResourceManager::LoadEngineResource<Texture>("stop_icon", "res/engine_files/controls/stop.png");
    ResourceManager::LoadEngineResource<Texture>("move_icon", "res/engine_files/controls/move.png");

    ResourceManager::LoadProjectResource<Shader>("test_shader", "/shaders/experimental/");
    ResourceManager::LoadProjectResource<TextureAtlas>("spritesheet", "/textures/testing.atlas");

    Renderer2D::Init();
    ImGuiLayer::Init();
  
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            std::string id = "entity_" + std::to_string(i) + std::to_string(j);
            EngineData::CurrentScene().CreateEntity(id);

            Entity* e = EngineData::CurrentScene().FindEntity(id);
            Transform& t = e->GetComponent<Transform>();
            t.position.x = i * 128;
            t.position.y = j * 128;
            t.scale.x = 128;
            t.scale.y = 128;
        }
    }

    Entity* e = EngineData::CurrentScene().FindEntity("entity_00");
    Entity* e1 = EngineData::CurrentScene().FindEntity("entity_01");
    Entity* e2 = EngineData::CurrentScene().FindEntity("entity_11");
    Entity* e3 = EngineData::CurrentScene().FindEntity("entity_10");
    e->AddChild(e1);
    e->AddChild(e2);
    e2->AddChild(e3);

    for (std::string& s : e->GetChildren()) {
        LOG_INFO("{}", s.c_str());
    }
}

void Firefly::Engine::Destroy() {
    EngineData::Serialize();
}

void Firefly::Engine::Update(float dt) {
    EngineData::CurrentScene().Update(dt);

    glm::vec2 worldMouse = EngineData::CurrentScene().cam.ScreenToWorld(Input.mouse);

    Entity* e = EngineData::CurrentScene().FindEntity("entity_00");
    if (e->HasComponent<Transform>()) {
        Transform& t = e->GetComponent<Transform>();
        t.position = glm::vec3(worldMouse.x, worldMouse.y, 0);

        if (Input.IsKeyDown(GLFW_KEY_E)) {
            t.rotation += 3;
        }
        if (Input.IsKeyDown(GLFW_KEY_Q)) {
            t.rotation -= 3;
        }
        if (Input.IsMouseDown(0)) {
        }
    }
}

void Firefly::Engine::Draw() {
    ImGuiLayer::Draw();
    EngineData::CurrentScene().Draw();
}

void Firefly::Engine::Resize(int width, int height) {
    EngineData::CurrentScene().cam.UpdateProj(width, height);
}
}
