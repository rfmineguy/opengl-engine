#include "test.h"
#include "../renderer/basicRenderer2d.h"
#include "../renderer/orthoCamera.h"

namespace test {
    class TestGame : public Test {
    public:
        TestGame();
        ~TestGame();
        
        void Update(float dt) override;
        void Render() override;
        void Resize(int width, int height) override;
        void ImGuiRender() override;

    private:
        BasicRenderer2D renderer;
        OrthoCamera camera;
        entt::registry reg;
    };
}
