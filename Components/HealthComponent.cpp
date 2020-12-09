//
// Created by marco on 12/7/20.
//

#include <iostream>
#include "HealthComponent.hpp"

float HealthComponent::getHealth() const {
    return this->_healthPoints;
}

void HealthComponent::setHealth(float newHealthPoints) {
    this->_healthPoints = newHealthPoints;
}

void HealthComponent::doDamage(float amountOfHealthPoints) {
    std::cout << "HealthComponent: Damaged from " << this->getHealth() << " to " << this->_healthPoints  << std::endl;

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
