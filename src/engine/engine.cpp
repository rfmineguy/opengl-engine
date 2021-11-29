#include "engine.h"

Engine::Engine() {
    Create();
}

Engine::~Engine() {
    Renderer2D::DeInit();
}

void Engine::Create() {
    ResourceManager::Init();
    ResourceManager::LoadShader("test_shader", "experimental");
    ResourceManager::LoadTextureAtlas("spritesheet", "testing");
    ResourceManager::PrintContents();

    Renderer2D::Init();
    ImGuiLayer::Init();
    
    GameObject& object = Registry::RegisterGameObject("object0");
    Registry::AddComponent<Transform>(object, 80, 84, 120, 120, 0);
    Registry::AddComponent<Identifier>(object, "0");
    Registry::AddComponent<Renderable>(object, "spritesheet", "bigx");    
    LOG_DEBUG("Added Registry object");

    GameObject& object1 = Registry::RegisterGameObject("object1");
    Registry::AddComponent<Transform>(object1, 80, 84, 120, 120, 0);
    Registry::AddComponent<Identifier>(object1, "1");
    Registry::AddComponent<Renderable>(object1, "spritesheet", "bigx");    
    
    LOG_DEBUG("End Create");
}

void Engine::Update(float dt) {
    camera.Movement();

    glm::vec2 worldMouse = camera.ScreenToWorld(Input.mouse);
    Registry::GetComponent<Transform>("object0").position = glm::vec3(worldMouse.x, worldMouse.y, 0);
    if (Input.keys[GLFW_KEY_E]) {
        Registry::GetComponent<Transform>("object0").rotation += 2;
    }
    if (Input.keys[GLFW_KEY_Q]) {
        Registry::GetComponent<Transform>("object0").rotation -= 2;
    }
    if (Input.scrollYOffset != 0) {
        Registry::GetComponent<Transform>("object0").scale += (glm::vec3(Input.scrollYOffset, Input.scrollYOffset, 0) * glm::vec3(5));
    }
    LOG_DEBUG("End Update");
}

void Engine::Draw() {
    Renderer2D::DrawRegistry(camera);
    ImGuiLayer::Draw();

    LOG_DEBUG("End Draw");
}

void Engine::Resize(int width, int height) {
    camera.UpdateProj(width, height);
}
