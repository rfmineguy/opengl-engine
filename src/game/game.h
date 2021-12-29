#pragma once

#include "../engine/engineData.h"
#include "../engine/scene.h"
#include "../gameobject/entity.h"
#include "../window/inputData.h"
#include "../util/resourceManager.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Firefly {
class Game {
public:
    Game() = default;
    ~Game() = default;
    virtual void Create() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;

protected:
    Scene* Scene() { return &EngineData::CurrentScene(); }
};
}
