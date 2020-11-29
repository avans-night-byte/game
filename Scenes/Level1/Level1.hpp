#pragma once

#include "../../../Engine/Rendering/Level.hpp"
#include "../../../Engine/Input/Input.hpp"
#include "../../Components/CharacterComponent.h"

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
