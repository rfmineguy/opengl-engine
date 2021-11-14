#include "testGame.h"
#include "../components/components.h"
#include "../window/inputData.h"

namespace test {
    TestGame::TestGame() {
        int width=10,height=10;
        for (int i = 0; i < 3; i++) {
            int x = i % width;
            int y = i / width;
            GameObject object(reg);
            object.AddComponent<Transform>(x * 64, y * 64, 120, 120, 0);
            object.AddComponent<Identifier>(std::to_string(i));
            if (i % 2 == 0) {
                object.AddComponent<Renderable>("bigx");   //use the checkmark texture from the atlas
            }
            else {
                object.AddComponent<Renderable>("hi");
            }
            objects.push_back(object);

        }
    }

    TestGame::~TestGame() {
        objects.clear();
        renderer.Cleanup();
        std::cout << "TestGame Destructor" << std::endl;
        //NOTE entt registry automatically cleaned
    }


     void TestGame::Update(float dt) {
        camera.Movement();
        renderer.GetShader().Bind();
        renderer.GetShader().Set4fv("view", camera.GetView());
        renderer.GetShader().Set4fv("projection", camera.GetProj());
        
        //TODO : Map mouseX and mouseY to world space somehow. The xpos and ypos drift if you move
        //  the camera too far
       
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
    }

    void TestGame::Render() {
        renderer.Draw(objects);
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
