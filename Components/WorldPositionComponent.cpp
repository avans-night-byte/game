#include "WorldPositionComponent.hpp"

void WorldPositionComponent::setLocation(const float &x, const float &y) {
    this->x = &x;
    this->y = &y;
}


void WorldPositionComponent::update() {}

Component *WorldPositionComponent::Clone(EntityId entityId) const {
    return new WorldPositionComponent(entityId);
}

std::string WorldPositionComponent::name() const {
    return "";
}
