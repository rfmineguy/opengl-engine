#include "../registry.h"

namespace Firefly {
class Scene {
public:
    Scene();
    ~Scene();
    void Draw();
    void Update(float dt);
    GameObject& FindGameObject(const std::string& name);
    GameObject& CreateGameObject(const std::string& name);
};
}
