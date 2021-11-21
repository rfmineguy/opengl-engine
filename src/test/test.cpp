#include "test.h"

namespace test {
    TestMenu::TestMenu(Test*& currentTestPointer):
        mCurrentTest(currentTestPointer)
    {
    }

    void TestMenu::ImGuiRender() {
       for (auto& test : tests) {
            if (ImGui::Button(test.first.c_str())) {
                mCurrentTest = test.second();
            }
       } 
    }
}
