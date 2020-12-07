#pragma once

#include "../LevelBase.hpp"

class TMXLevel;
class Input;
class CharacterComponent;
class RenderingAPI;
class PhysicsAPI;


class Level1 : public LevelBase {
private:
    TMXLevel* _level;
    CharacterComponent& characterComponent;

public:
    explicit Level1(CharacterComponent& characterComponent);

    ~Level1();
    void render();

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;
};
