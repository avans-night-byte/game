#pragma once


#include "../../../Engine/Rendering/Level.hpp"
#include "../../Components/CharacterComponent.h"

class LevelCharlie {
private:
    Level* _level;
    unique_ptr<CharacterComponent> characterComponent;
public:
    LevelCharlie(EngineRenderingAPI& engineRenderingApi);
    ~LevelCharlie();
    void render(EngineRenderingAPI& engineRenderingAPI);

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};