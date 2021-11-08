#pragma once

#include "test.h"
//#include "../render_data/transform.h"
#include "../render_data/shader.h"
#include "../render_data/vertex.h"
//#include "../renderer/batch.h"
//#include "../renderer/instancedRenderer.h"
//#include "../renderer/basicRenderer2d.h"

#include "../renderer/orthoCamera.h"

namespace test {
    class TestShaderDev : public Test {
    public:
        TestShaderDev();
        ~TestShaderDev();

        void Update(float dt) override;
        void Render() override;
        void Resize(int width, int height) override;
        void ImGuiRender() override;

    private:
        float time;

    private:
        //Batch batch;
        //InstancedRenderer renderer;
        //BasicRenderer2D renderer;
        OrthoCamera camera;
        //PerspectiveCamera camera;

        //std::vector<Transform> transforms;
    };
}
