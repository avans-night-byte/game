#pragma once

class TMXLevel;
class Input;
class CharacterComponent;
class RenderingAPI;
class PhysicsAPI;


class Level1 {
private:
    TMXLevel* _level;
    CharacterComponent& characterComponent;

public:
    explicit Level1(CharacterComponent& characterComponent, RenderingAPI& renderingApi, PhysicsAPI& enginePhysicsApi);
    ~Level1();
    void render(RenderingAPI& renderingApi);

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};
