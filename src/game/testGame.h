#include "game.h"

namespace Firefly {
class TestGame: public Game {
public:
    TestGame();
    ~TestGame();
    void Create() override;
    void Update(float dt) override;
    void Render() override;
};
}
