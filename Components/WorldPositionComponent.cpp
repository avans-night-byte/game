#include "WorldPositionComponent.hpp"

void WorldPositionComponent::setLocation(const float& x, const float& y) {
    this->x = &x;
    this->y = &y;
}

void WorldPositionComponent::update() {}