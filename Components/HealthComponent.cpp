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
}

void HealthComponent::render() {
    Vector2 vec1(10, 10);
    Vector2 vec2(100, 10);
    _renderingApi.drawLine(vec1, vec2);
}

void HealthComponent::update(const Input &inputSystem) {

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
