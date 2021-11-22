#include "testGame.h"
#include "../components/components.h"
#include "../window/inputData.h"
#include "../util/resourceManager.h"

namespace test {
    TestGame::TestGame() {
        LOG_INFO("Begin TestGame");
        ResourceManager::Init();
        LOG_INFO("Begin Loading Resources");
        ResourceManager::LoadShader("test_shader", "experimental");
        ResourceManager::LoadTextureAtlas("spritesheet", "testing");
        LOG_INFO("End Loading Resources");
        ResourceManager::PrintContents();

        renderer.Init();

        objects.reserve(2);

        GameObject& object = objects.emplace_back(reg);
        object.AddComponent<Transform>(80, 84, 120, 120, 0);
        object.AddComponent<Identifier>("0");
        object.AddComponent<Renderable>("bigx");
       
        GameObject& object2 = objects.emplace_back(reg);
        object2.AddComponent<Transform>(20, 20, 55, 55, 0);
        object2.AddComponent<Identifier>("1");
        object2.AddComponent<Renderable>("check");

        LOG_DEBUG("{}", reg.size());
        LOG_DEBUG("{}", objects.size());
    }

    TestGame::~TestGame() {
        renderer.Cleanup();
        objects.clear();
        
        std::cout << "TestGame Destructor" << std::endl;
        LOG_WARN("Entt registry size {} capacity {}", reg.size(), reg.capacity());
        //NOTE entt registry automatically cleaned
    }

     void TestGame::Update(float dt) {
        //LOG_DEBUG("Update");
        camera.Movement();
        renderer.GetShader()->Bind();
        renderer.GetShader()->Set4fv("view", camera.GetView());
        renderer.GetShader()->Set4fv("projection", camera.GetProj());
       
        //LOG_DEBUG("End Shader Modification");

        if (objects[0].HasComponent<Transform>()) {
            glm::vec2 world = camera.ScreenToWorld(Input.mouse);
            objects[0].GetComponent<Transform>().position = glm::vec3(world.x, world.y, 0);
            if (Input.keys[GLFW_KEY_E]) {
                objects[0].GetComponent<Transform>().rotation++;
            }
            if (Input.keys[GLFW_KEY_Q]) {
                objects[0].GetComponent<Transform>().rotation--;
            }
        }
        //LOG_DEBUG("End Update");
    }

    void TestGame::Render() {
        //LOG_DEBUG("Render");
        renderer.Draw(objects);
        //LOG_DEBUG("End Render");
    }

    void TestGame::Resize(int width, int height) {
        camera.UpdateProj(width, height);
    }

    void TestGame::ImGuiRender() {
        glm::vec2 world = camera.ScreenToWorld(Input.mouse);
        //ImGui::Text("Draw Calls %d", renderer.drawCalls);
        ImGui::Text("Mouse %0.4f %0.4f", Input.mouse.x, Input.mouse.y);
        ImGui::Text("Mouse world %0.4f %0.4f", world.x, world.y);
        //ImGui::Checkbox("Wireframe Rendering", &renderer.drawWireframe);
    }
}
