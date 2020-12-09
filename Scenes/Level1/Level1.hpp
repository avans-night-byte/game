#pragma once

#include "../LevelBase.hpp"

class TMXLevel;
class Input;
class CharacterComponent;
class RenderingAPI;
class PhysicsAPI;


class Level1 {
private:
    TMXLevel* _level;
    CharacterComponent* characterComponent;

public:
    explicit Level1(TMXLevel* tmxLevel, CharacterComponent* characterComponent);

    ~Level1();
    void render();

    void update(const Input &inputSystem);

    void fixedUpdate(const float &deltaTime);
};
