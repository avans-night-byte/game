#pragma once


#include "../../../Engine/Rendering/Level.hpp"
#include "../../Components/CharacterComponent.h"

class LevelCharlie {
private:
    Level* _level;
    CharacterComponent& characterComponent;

public:
    LevelCharlie(CharacterComponent& characterComponent, EngineRenderingAPI& engineRenderingApi, PhysicsAPI& enginePhysicsApi);
    ~LevelCharlie();
    void render(EngineRenderingAPI& engineRenderingAPI);

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};