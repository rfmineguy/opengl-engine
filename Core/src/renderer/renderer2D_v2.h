#pragma once

#include "core/components/components.h"
#include "framebuffer.h"
#include "orthoCamera.h"
#include "shader.h"
#include "primitives/quad.h"

namespace Firefly {
class Renderer2D_V2 {
public:
    static Renderer2D_V2& Get() {
        static Renderer2D_V2 renderer2D_V2;
        return renderer2D_V2;
    }

    static void Init();
    static void Shutdown();

    static void BeginScene(OrthoCamera& camera, FrameBuffer& fb, bool drawWireframe = false);
    static void BeginScene(OrthoCamera& camera, FrameBuffer& fb, glm::vec4 clearColor, bool drawWireframe = false);
    static void BeginScene(OrthoCamera& camera, FrameBuffer& fb, Shader& shader, glm::vec4 clearColor, bool drawWireframe = false);
    static void EndScene();

    //quad rendering (default)
    static void DrawQuad(Transform& t, TextureAtlas* textureAtlas, const std::string& region);
    static void DrawQuad(Transform& t, SpriteRenderer& sp);

    //Line rendering
    static void DrawLine(glm::vec2 start, glm::vec2 end, float thickness);

private:
    static void StartBatch();
    static void NextBatch();

private:
    unsigned int textureVbo;
    FrameBuffer* fb;
    Shader* shader;
    bool sceneEnded, sceneBegan, initialized;
    
    Quad quad;
    unsigned int drawCallCount;
};
}
