//
// Created by sascha on 12/5/20.
//

#include "HealthComponent.hpp"


float HealthComponent::damage(float amount) {
    _hp -= amount;

    if(_hp < 0)
        _hp = 0;

    return _hp;
}

float HealthComponent::getHealth() const {
    return _hp;
}


/**
 * Renders a health bar above the item.
 */
void HealthComponent::render() {
    //TODO
}

HealthComponent::HealthComponent(float startingHp, EngineRenderingAPI &engineRenderingApi): _engineRenderingApi(engineRenderingApi), _hp(startingHp) {

}
