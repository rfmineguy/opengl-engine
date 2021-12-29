#include "testGame.h"

namespace Firefly {
TestGame::TestGame() {}

TestGame::~TestGame() {}

void TestGame::Create() {
    ResourceManager::LoadProjectResource<TextureAtlas>("pong_atlas", "textures/pong_atlas.png");
    Entity* e = Scene()->CreateEntity("left_paddle");
    Entity* e1 = Scene()->CreateEntity("right_paddle");
}

void TestGame::Update(float dt) {
    Scene()->Update(dt);
    Entity* e = Scene()->FindEntity("left_paddle");
    Transform& t = e->GetComponent<Transform>();
    glm::vec3 dir;
    if (Input.IsKeyDown(GLFW_KEY_W)) dir.y -= 10 * dt;
    if (Input.IsKeyDown(GLFW_KEY_S)) dir.y += 10 * dt;
    t.position += dir;

    e = Scene()->FindEntity("right_paddle");
    t = e->GetComponent<Transform>();
    glm::vec3 dir2;
    if (Input.IsKeyDown(GLFW_KEY_UP)) dir2.y -= 10 * dt;
    if (Input.IsKeyDown(GLFW_KEY_DOWN)) dir2.y += 10 * dt;
    t.position += dir2; 
}

void TestGame::Render() {
    Scene()->Draw();
}
}

