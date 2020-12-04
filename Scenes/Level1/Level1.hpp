#pragma once

class Level;
class Input;
class CharacterComponent;
class EngineRenderingAPI;
class PhysicsAPI;


class Level1 {
private:
    Level* _level;
    CharacterComponent& characterComponent;

public:
    explicit Level1(CharacterComponent& characterComponent, EngineRenderingAPI& engineRenderingApi, PhysicsAPI& enginePhysicsApi);
    ~Level1();
    void render(EngineRenderingAPI& engineRenderingAPI);

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};
