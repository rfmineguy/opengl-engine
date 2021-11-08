#include "testClearColor.h"
#include "../../vendor/imgui/imgui.h"


namespace test {
    TestClearColor::TestClearColor() 
:mClearColor { 105 / 255.f, 86 / 255.f, 77 / 255.f, 1.0f }
    {

    }

    TestClearColor::~TestClearColor() {

    }

    void TestClearColor::Update(float dt) {

    }

    void TestClearColor::Render() {
        glClearColor(mClearColor[0],mClearColor[1],mClearColor[2],mClearColor[3]);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    
    void TestClearColor::Resize(int width, int height) {

    }

    void TestClearColor::ImGuiRender() {
        ImGui::Begin("ClearColorTest");
        ImGui::ColorEdit4("Clear color", mClearColor);
        ImGui::End();
    }
}
