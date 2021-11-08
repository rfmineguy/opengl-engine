#pragma once

#include "test.h"
#include "../render_data/shader.h"
#include "../render_data/vertex.h"
#include "../renderer/batch.h"

namespace test {
    class TestTriangle : public Test {
    public:
        TestTriangle();
        ~TestTriangle();

        void Update(float dt) override;
        void Render() override;
        void Resize(int width, int height) override;
        void ImGuiRender() override;
 
    private:
        Batch batch;
        Geometry quad1, quad2;
    };
}
