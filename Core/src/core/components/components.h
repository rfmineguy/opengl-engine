#pragma once
#include "../corepch.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>

#include "renderer/region.h"
#include "renderer/texture.h"
#include "renderer/textureAtlas.h"
#include "entt/entity/entity.hpp"

/* Transform component
 *   position, scale, rotation
 */
struct Transform {
    glm::mat4 transform;
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;

    Transform() = default;
    Transform(float x, float y, float xscale, float yscale, float _rotation) {
        position = glm::vec3(x, y, 0);
        scale = glm::vec3(xscale, yscale, 1);
        rotation = _rotation;
    }

    Transform(glm::vec3 _position, glm::vec3 _scale, float _rotation) {
        position = _position;
        scale = _scale;
        rotation = _rotation;
    }
    /*
    glm::mat4 CalcModelMatrix() {
        glm::mat4 model(1.0);
        model = glm::translate(model, position);
        model = glm::translate(model, glm::vec3(0.5f, 0.5f, 0.0f));
        model = glm::scale(model, scale);
        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0, 0, 1));
        model = glm::translate(model, -glm::vec3(0.5f, 0.5f, 0.5f));
        transform = model;
        return model;
    }*/

    glm::mat4 CalcModelMatrix() {
        return glm::mat4(1.0);
    }
};

/* Orthographic Camera component
 *  will handle camera functions and enable there to be more than one camera
 *   in the scene at a time
 */
struct OrthoCameraTest {
    const glm::vec4 GetView();
    const glm::mat4 GetProj();
    const glm::mat4 GetViewProj();

    void SetPos(glm::vec3 pos);
    void SetRotation(float rotation);
    void SetScale(float sx, float sy);
    void DeltaPos(float dx, float dy);
    void SetViewportSize(int width, int height);
    
    const glm::vec2 ScreenToWorld(const glm::vec2 mouseCoord);
    const glm::vec2 WorldToScreen(const glm::vec2 worldCoord);
    void UpdateProj(int width, int height);

private:
    void RecalculateView();

private:
    glm::mat4 view, proj, view_proj;
};

/* Identifier component
 *  gives a gameobject a display name basically 
 */
struct Identifier {
    std::string id;
    std::string displayName;
};

/* Renderable component
 *   gives the ability to render a GameObject with a texture
 */
struct Renderable {
    std::string resourceId;     //id of the loaded resource
    std::string atlasSubRegionName; //name of the subregion in the atlas
    Region region = {};
};

/* Animator component
 *   a controller for the sprite renderer (dependent on it)
 *   the sprite renderer must have a spritesheet
 */
struct AnimatedRenderable : Renderable {
    int timer;
    int delay;
    int currentFrameId, lastFrameId;
    bool looping;
    
    //return id of the current frame
    int animate() {
        timer ++;
        if (timer > delay) {
            currentFrameId++;
        }
        if (currentFrameId > lastFrameId) {
            currentFrameId = 0;
        }
        return currentFrameId;
    }
};

/*  Script component
 *    * will be used as the root component/object for programmable gameobject
 */
struct Script {
    std::string luaScriptPath;
};

struct SpriteRenderer {
    bool isSingleImage;
    Firefly::TextureAtlas* texture;
    glm::vec4 colorTint;

    std::string atlasSubRegionName;
};

struct Relationship {
    bool isParent, isChild;
    int level;
    std::string parent;
    std::vector<std::string> children;
};
