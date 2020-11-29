//
// Created by sascha on 11/27/20.
//

#ifndef NIGHTBYTE_LEVEL1_HPP
#define NIGHTBYTE_LEVEL1_HPP


#include "../../../Engine/Rendering/Level.hpp"
#include "../../../Engine/Input/Input.hpp"
#include "../../Components/CharacterComponent.h"

class Level1 {
private:
    Level* _level;
    unique_ptr<CharacterComponent> characterComponent;
public:
    Level1(EngineRenderingAPI& engineRenderingApi);
    ~Level1();
    void render(EngineRenderingAPI& engineRenderingAPI);

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};


#endif //NIGHTBYTE_LEVEL1_HPP
