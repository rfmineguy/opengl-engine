#include "testGame.h"
#include "../components/components.h"

namespace test {
    TestGame::TestGame() {
        int width=10,height=10;
        for (int i = 0; i < 10; i++) {
            const auto entity = reg.create();
            int x = i % width;
            int y = i / width;
            reg.emplace<Transform>(entity, x * 64, y * 64, 48, 48, 180);
            reg.emplace<Identifier>(entity, std::to_string(i));
        }

        auto view = reg.view<Transform>();
        for (auto entity : view) {
            auto &trans = view.get<Transform>(entity);
            trans.Print();
        }
    }

    TestGame::~TestGame() {
        //NOTE entt registry automatically cleaned
    }

    void TestGame::Update(float dt) {
        camera.Movement();
        renderer.GetShader().Bind();
        renderer.GetShader().Set4fv("view", camera.GetView());
        renderer.GetShader().Set4fv("projection", camera.GetProj());
    }

    void TestGame::Render() {
        renderer.Draw(reg);
    }

    void TestGame::Resize(int width, int height) {
        camera.UpdateProj(width, height);
    }

    void TestGame::ImGuiRender() {
        ImGui::Text("Draw Calls %d", renderer.drawCalls);
    }
}
