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
    ResourceManager::LoadProjectResource<Shader>("test_shader", "/shaders/experimental/");
    ResourceManager::LoadProjectResource<TextureAtlas>("spritesheet", "/textures/testing.atlas");
    ResourceManager::PrintContents();

    Renderer2D::Init();
    ImGuiLayer::Init();
  
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::string id = "entity_" + std::to_string(i) + std::to_string(j);
            EngineData::CurrentScene().CreateEntity(id);

            Entity* e = EngineData::CurrentScene().FindEntity(id);
        }
    }
}

void Firefly::Engine::Destroy() {
    EngineData::Serialize();
}

void Firefly::Engine::Update(float dt) {
    camera.Movement();

    //LOG_INFO("{}", EngineData::CurrentScene().reg.size());

    glm::vec2 worldMouse = camera.ScreenToWorld(Input.mouse);
    /*
    Registry::GetComponent<Transform>("object00").position = glm::vec3(worldMouse.x, worldMouse.y, 0);
    if (Input.keys[GLFW_KEY_E]) {
        Registry::GetComponent<Transform>("object00").rotation += 2;
    }
    if (Input.keys[GLFW_KEY_Q]) {
        Registry::GetComponent<Transform>("object00").rotation -= 2;
    }
    if (Input.scrollYOffset != 0) {
        Registry::GetComponent<Transform>("object00").scale += (glm::vec3(Input.scrollYOffset, Input.scrollYOffset, 0) * glm::vec3(5));
    }
    */
}

void Firefly::Engine::Draw() {
    Firefly::ImGuiLayer::Draw();
    //Renderer2D::DrawRegistry(camera);
}

void Firefly::Engine::Resize(int width, int height) {
    camera.UpdateProj(width, height);
}
}
