class Game {
public:
    Game();
    ~Game();
    virtual void OnCreate();
    virtual void OnUpdate(float dt);
    virtual void OnRender();
    virtual void OnResize();
    virtual void OnCleanup();
};
