#pragma once

//#include "../registry.h"
#include "../render_data/shader.h"
#include "../render_data/geometry.h"
#include "../components/components.h"
#include "../util/geometryUtil.hpp"
#include "../util/resourceManager.h"
#include "../renderer/orthoCamera.h"
#include "../renderer/framebuffer.h"
#include "../gameobject/entity.h"

//Renderer2D is a friend class of Registry
namespace Firefly {
class Renderer2D {
public:
    static Renderer2D& Get() {
        static Renderer2D renderer2d;
        return renderer2d;
    }

    //call at very beginning of game and never again
    static void Init() {
        LOG_DEBUG("Renderer2D Init");
        Get().InitImpl();
    }

    static void DeInit() {
        Get().DeInitImpl();
    }

    static void ToggleWireframe() {
        Get().wireframe = !Get().wireframe;
    }
   
    //draw entity 
    static void Draw(Entity& entity, OrthoCamera& camera) {
        Get().DrawImpl(entity, camera);
    }

    static void DrawQuad(Transform& t, Renderable& r, OrthoCamera& camera) {
        Get().DrawQuadImpl(t, r, camera);
    }
    
    //draw everything drawable currently in the registry
    static void DrawRegistry(OrthoCamera& camera) {
        Get().DrawRegistryImpl(camera);
    }

private:
    void DrawQuadImpl(Transform& t, Renderable& r, OrthoCamera& camera) {
        Get().shader->Bind();
        Get().shader->Set4fv("view", camera.GetView());
        Get().shader->Set4fv("projection", camera.GetProj());
        
        Get().textureAtlas->Unbind();
        Get().textureAtlas = ResourceManager::GetProjectResource<TextureAtlas>(r.resourceId);
        Get().textureAtlas->Bind();

        if (r.region.empty) {
            r.region = Get().textureAtlas->GetRegion(r.atlasSubRegionName);
            r.region.empty = false;
        }

        //  CALCULATE MODELMATRIX
        //
        glm::mat4 model = glm::mat4(1.0);
        model = glm::translate(model, t.position);
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
        model = glm::scale(model, t.scale);
        model = glm::rotate(model, glm::radians(t.rotation), glm::vec3(0, 0, 1));
        model = glm::translate(model, -glm::vec3(0.5f, 0.5f, 0.0f));

        //texturing
        glm::vec2 texCoord[4];
        texCoord[1] = r.region.topright; //topright
        texCoord[0] = r.region.bottomright; //bottomright
        texCoord[3] = r.region.bottomleft; //bottomleft
        texCoord[2] = r.region.topleft; //topleft

        //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);
        //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, quad.mIndices.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, Get().textureVbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord[0]) * 4, &texCoord[0], GL_STATIC_DRAW);
        //LOG_DEBUG("Set the texture coords");

        //
        //  DRAW VAO
        //
        Get().shader->Set4fv("model", model);
        //LOG_DEBUG("Set the model matrix");
        glDrawElements(GL_TRIANGLES, Get().quad.mIndices.size(), GL_UNSIGNED_INT, 0);
        Get().drawCalls++;
    }
    
    void DrawImpl(Entity& entity, OrthoCamera& camera) {
        if (!Get().isInitialized) {
            LOG_ERROR("Renderer2D not initialized! Initialize it with Renderer2D::Init()");
            return;
        }
        
        //Enable/Disable wireframe
        Get().wireframe ?
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE):
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        Get().shader->Bind();
        Get().shader->Set4fv("view", camera.GetView());
        Get().shader->Set4fv("projection", camera.GetProj());

        if (entity.HasComponent<Renderable>() && entity.HasComponent<Transform>()) {
            Transform& t = entity.GetComponent<Transform>();
            Renderable& r = entity.GetComponent<Renderable>();

            Get().textureAtlas->Unbind();
            Get().textureAtlas = ResourceManager::GetProjectResource<TextureAtlas>(r.resourceId);
            Get().textureAtlas->Bind();

            if (r.region.empty) {
                r.region = Get().textureAtlas->GetRegion(r.atlasSubRegionName);
                r.region.empty = false;
            }

            //  CALCULATE MODELMATRIX
            //
            //glm::mat4 model = glm::mat4(1.0);
            
            glm::mat4& model = entity.GetComponent<Transform>().transform;
            model = glm::mat4(1.0);
            model = glm::translate(model, t.position);
            model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
            model = glm::scale(model, t.scale);
            model = glm::rotate(model, glm::radians(t.rotation), glm::vec3(0, 0, 1));
            model = glm::translate(model, -glm::vec3(0.5f, 0.5f, 0.0f));

            //texturing
            glm::vec2 texCoord[4];
            texCoord[1] = r.region.topright; //topright
            texCoord[0] = r.region.bottomright; //bottomright
            texCoord[3] = r.region.bottomleft; //bottomleft
            texCoord[2] = r.region.topleft; //topleft

            //glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);
            //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, quad.mIndices.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, Get().textureVbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(texCoord[0]) * 4, &texCoord[0], GL_STATIC_DRAW);
            //LOG_DEBUG("Set the texture coords");

            //
            //  DRAW VAO
            //
            Get().shader->Set4fv("model", model);
            //LOG_DEBUG("Set the model matrix");
            glDrawElements(GL_TRIANGLES, Get().quad.mIndices.size(), GL_UNSIGNED_INT, 0);
            Get().drawCalls++;
        }
    }
    void DrawRegistryImpl(OrthoCamera& camera) {
        //LOG_DEBUG("Bind framebuffer");
        /*
        frameBuffer.Bind();
        glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        for (const auto &entry: Registry::Get().entities) {
            Draw(*entry.second, camera);
        }
        frameBuffer.Unbind();
        */
        //LOG_DEBUG("Unbind framebuffer");
    }

    void InitImpl() {
        LOG_DEBUG("InitImpl");
        if (!isInitialized) {
            LOG_DEBUG("Initializing 2D Renderer");
            textureAtlas = ResourceManager::GetProjectResource<TextureAtlas>("spritesheet");
            shader = ResourceManager::GetProjectResource<Shader>("test_shader");

            initQuad(quad);
            glGenVertexArrays(1, &vao);
            glGenBuffers(1, &vbo);
            glGenBuffers(1, &ebo);
            int verticesSize = sizeof(quad.mVertices[0]) * quad.mVertices.size();
            int indicesSize = sizeof(quad.mIndices[0]) * quad.mIndices.size();
    
            glBindVertexArray(vao);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, verticesSize, quad.mVertices.data(), GL_STATIC_DRAW);
    
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, quad.mIndices.data(), GL_STATIC_DRAW);
            
            //ATTRIBUTES
            {
                //position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(struct Vertex, pos));
                glEnableVertexAttribArray(0);

                glGenBuffers(1, &textureVbo);
                glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
    
                //tex coord attribe
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*) 0);
                glEnableVertexAttribArray(1);
            }
            
            //FRAMEBUFFER
            frameBuffer.Resize(1280, 720);

            LOG_DEBUG("Initialized 2D Renderer");
            isInitialized = true;
        }
        else {
            LOG_WARN("2D Renderer already initialized..");
        }
    }
    void DeInitImpl() {
        if (isInitialized) {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
            Get().textureAtlas->Unbind();
            Get().shader->Unbind();

            glBindVertexArray(0);
            glDeleteVertexArrays(1, &vao);
            glDeleteBuffers(1, &vbo);
            glDeleteBuffers(1, &ebo);

            isInitialized = false;
            LOG_INFO("2D Renderer uninitialized");
        } 
        else {
            LOG_WARN("2D Renderer never initialized, unable to uninitialize");
        }
    }
private:
    bool wireframe = false;
    bool isInitialized = false;
    int drawCalls = 0;

    Geometry quad;
    Shader* shader;
    TextureAtlas* textureAtlas;
    unsigned int vao, vbo, ebo;
    unsigned int textureVbo;

public:
    FrameBuffer frameBuffer;

    friend class ImGuiPropertiesPanel;
};


}
