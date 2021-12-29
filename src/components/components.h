#pragma once
#include "../corepch.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../render_data/region.h"
#include "../render_data/textureAtlas.h"
#include "entt/entity/entity.hpp"

/* Transform component
 *   position, scale, rotation
 */
struct Transform {
    glm::mat4 transform;
    glm::vec3 position;
    glm::vec3 scale;
    float rotation; 

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

    void Print() {
        printf("pos {%0.4f %0.4f}, scale {%0.4f %0.4f %0.4f}, rot {%0.4f}\n",
                position.x, position.y,
                scale.x, scale.y, scale.z,
                rotation);
    }
};

/* Orthographic Camera component
 *  will handle camera functions and enable there to be more than one camera
 *   in the scene at a time
 */
struct OrthoCameraTest {
    const glm::vec4 GetView();
    const glm::mat4 GetProj();
    void SetPos(glm::vec3 pos);
    void SetRotation(float rotation);
    void SetScale(float sx, float sy);
    void DeltaPos(float dx, float dy);
    void SetViewportSize(int width, int height);

    glm::vec2 ScreenToWorld(const glm::vec2 mouseCoord);
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
    std::string resourceId;
    std::string atlasSubRegionName;
    
    void Draw() {
    }
};

struct Relationship {
    bool isParent, isChild;
    int level;
    std::string parent;
    std::vector<std::string> children;
};
