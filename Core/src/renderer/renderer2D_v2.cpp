#include "renderer2D_v2.h"
#include "util/resourceManager.h"
#include "util/geometryUtil.hpp"

namespace Firefly {
    void Renderer2D_V2::Init() {
        ResourceManager::LoadEngineResource<Shader>("base-shader", "res/shader/base/");
        Get().sceneEnded = true;
        Get().sceneBegan = false;
        Get().initialized = true;

        LOG_DEBUG("Initialized Renderer2D_V2");
    }

    void Renderer2D_V2::Shutdown() {
        LOG_DEBUG("Shutdown Renderer2D_V2");       
    }

    //drawWireframe default value = false
    void Renderer2D_V2::BeginScene(OrthoCamera& camera, FrameBuffer& _fb, bool drawWireframe) {
        if (Get().initialized) {
            BeginScene(camera, _fb, *ResourceManager::GetEngineResource<Shader>("base-shader"), glm::vec4(1.0), drawWireframe);
        }
        else {
            LOG_ERROR("Renderer2D not intiialized");
        }
    }

    void Renderer2D_V2::BeginScene(OrthoCamera& camera, FrameBuffer& _fb, glm::vec4 clearColor, bool drawWireframe) {
        BeginScene(camera, _fb, *ResourceManager::GetEngineResource<Shader>("base-shader"), clearColor, drawWireframe);
    }

    //drawWireframe default value = false
    void Renderer2D_V2::BeginScene(OrthoCamera& camera, FrameBuffer& _fb, Shader& _shader, glm::vec4 clearColor, bool drawWireframe) {
        if (!Get().sceneEnded) {
            LOG_ERROR("Scene not ended. UseEndScene()");
            return;
        }

        drawWireframe ?
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


        Get().shader = &_shader;
        Get().fb = &_fb;
        Get().fb->Bind();
        glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        Get().shader->Bind();
        Get().shader->Set4fv("view", camera.GetView());
        Get().shader->Set4fv("projection", camera.GetProj());

        Get().sceneBegan = true;
        Get().sceneEnded = false;
    }

    void Renderer2D_V2::EndScene() {
        if (!Get().sceneBegan) {
            LOG_ERROR("Scene not started. Use BeginScene()");
            return;
        }

        Get().fb->Unbind();
        Get().shader->Unbind();

        Get().sceneBegan = false;
        Get().sceneEnded = true;
    }

    void Renderer2D_V2::DrawQuad(Transform& t, TextureAtlas* textureAtlas, const std::string& region) {
        if (Get().sceneEnded) {
            LOG_DEBUG("Scene ended, use BeginScene()");
            return;
        }

        Get().quad.Bind();
        textureAtlas->Bind();
        
        glm::mat4 modelMatrix = t.CalcModelMatrix();
        Region r = textureAtlas->GetRegion(region); //should just be normal 0-1 for "main" (rework texture system for this)
        glm::vec2 texCoord[4];
        texCoord[1] = r.topright; //topright
        texCoord[0] = r.bottomright; //bottomright
        texCoord[3] = r.bottomleft; //bottomleft
        texCoord[2] = r.topleft; //topleft

        glBindBuffer(GL_ARRAY_BUFFER, Get().quad.texVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord[0]) * 4, &texCoord[0], GL_STATIC_DRAW);
        

        Get().shader->Set4fv("model", modelMatrix);
        glDrawElements(GL_TRIANGLES, Get().quad.EBO_Size(), GL_UNSIGNED_INT, 0);

        Get().drawCallCount++;
    }

    void Renderer2D_V2::DrawQuad(Transform& t, SpriteRenderer& sp) {
        glm::mat4 modelMatrix = t.CalcModelMatrix();
        if (sp.isSingleImage) {
            DrawQuad(t, sp.texture, "main");
        }
        else {
            DrawQuad(t, sp.texture, sp.atlasSubRegionName);
        }
    }

    void Renderer2D_V2::DrawLine(glm::vec2 start, glm::vec2 end, float thickness) {

    }

    //Note: not implemented yet, batching will happen much later down the line
    void Renderer2D_V2::StartBatch() {}
    void Renderer2D_V2::NextBatch() {}
}
