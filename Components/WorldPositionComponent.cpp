#include "WorldPositionComponent.hpp"

void WorldPositionComponent::setLocation(const float& x, const float& y) {
    this->x = &x;
    this->y = &y;
}

void WorldPositionComponent::update() {}

std::unique_ptr<Component> WorldPositionComponent::Clone(EntityId entityId) {
    return std::unique_ptr<Component>();
}
