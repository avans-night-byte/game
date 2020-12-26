#include "HealthComponent.hpp"

#include <iostream>

float HealthComponent::getHealth() const {
    return this->_healthPoints;
}

void HealthComponent::setHealth(float newHealthPoints) {
    this->_healthPoints = newHealthPoints;
}

void HealthComponent::doDamage(float amountOfHealthPoints) {
    std::cout << "HealthComponent: Damaged from " << this->getHealth() << " to " << this->_healthPoints << std::endl;

    float newHealth = this->_healthPoints -= amountOfHealthPoints;

    if (newHealth <= 0) {
        this->die();
    } else {
        this->setHealth(newHealth);
    }
}

void HealthComponent::die() {
    std::cout << "HealthComponent: You died" << std::endl;
    this->setHealth(0);
    ResourceManager::getInstance()->quitLevel = true;
    ResourceManager::getInstance()->loadResource("GameOver");
}

void HealthComponent::render() {
    Vector2 vec1(10, 50);
    Vector2 vec2(20, 60);
    std::string color("000000");
    std::string colo2("ff1100");
    _renderingApi.drawRectangle(vec1, 500, 50, color, 255);
    _renderingApi.drawRectangle(vec2,  480.f / 100.f * _healthPoints, 30, colo2, 255);
}


void HealthComponent::update(const Input &inputSystem) {
    if (inputSystem.keyMap.type == KeyType::KeyUp) {
        _damageIsDone = false;
    } else if (!_damageIsDone && inputSystem.keyMap.code == "G") {
        doDamage(10);
        _damageIsDone = true;
    }
}

void HealthComponent::fixedUpdate(const float &deltaTime) {

}

std::string HealthComponent::name() const {
    return "HealthComponent";
}

Component *HealthComponent::build(EntityId entityId, const Components::component *component) {
    return new HealthComponent(entityId);
}

void HealthComponent::initialize(EntityObject &entityParent) {

}
