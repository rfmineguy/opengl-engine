#pragma once

#include "test.h"

namespace test {
    class TestClearColor : public Test {
    public:
        TestClearColor();
        ~TestClearColor();

        void Update(float dt) override;
        void Render() override;
        void Resize(int width, int height) override;
        void ImGuiRender() override;

    private:
        float mClearColor[4];
    };
}
