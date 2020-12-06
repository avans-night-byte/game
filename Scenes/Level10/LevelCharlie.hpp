#pragma once



class CharacterComponent;
class Input;
class TMXLevel;
class RenderingAPI;
class PhysicsAPI;

class LevelCharlie {
private:
    TMXLevel* _level;
    CharacterComponent& characterComponent;

public:
    LevelCharlie(CharacterComponent& characterComponent, RenderingAPI& engineRenderingApi, PhysicsAPI& enginePhysicsApi);
    ~LevelCharlie();
    void render(RenderingAPI& engineRenderingAPI);

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};