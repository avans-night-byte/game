//
// Created by sascha on 12/5/20.
//

#ifndef NIGHTBYTE_HEALTHCOMPONENT_HPP
#define NIGHTBYTE_HEALTHCOMPONENT_HPP


#include "../../API/Rendering/EngineRenderingAPI.hpp"

class HealthComponent {
private:
    float _hp = 0;
    EngineRenderingAPI &_engineRenderingApi;

public:
    HealthComponent(float startingHp, EngineRenderingAPI& engineRenderingApi);
    float damage(float amount);
    float getHealth() const;

    void render() ;
};


#endif //NIGHTBYTE_HEALTHCOMPONENT_HPP
