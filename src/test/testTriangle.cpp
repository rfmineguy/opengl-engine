#include "testTriangle.h"
#include <glm/fwd.hpp>

namespace test {

    //TODO there is a memory leak somewhere in the code, find it
    TestTriangle::TestTriangle()
    {
        batch.SetShader("basic");
    }

    TestTriangle::~TestTriangle() {
        
    }

    void TestTriangle::Update(float dt) {

    }

    void TestTriangle::Resize(int width, int height) {
    
    }

    void TestTriangle::Render() {
        glClearColor(0.4f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        batch.Begin(false);
        //batch.Add(quad1);
        //batch.Add(quad2);
        batch.Flush();
    }
    void TestTriangle::ImGuiRender() {
        ImGui::Text("Vertex count : %i", batch.Size());
    }
}
