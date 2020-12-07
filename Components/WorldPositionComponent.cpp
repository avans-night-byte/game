#include <Generated/level-resources.hxx>
#include "WorldPositionComponent.hpp"

void WorldPositionComponent::setLocation(const float &rX, const float &rY) {
    this->x = &rX;
    this->y = &rY;
}


void WorldPositionComponent::update() {}

void WorldPositionComponent::fixedUpdate(const float &deltaTime) {

}

std::string WorldPositionComponent::name() const {
    return "WorldPositionComponent";
}

Component *WorldPositionComponent::Clone(EntityId entityId, const LevelResources::component *component) {
    auto &resourceWorldPosition = component->worldPositionComponent().get();
    auto &position = resourceWorldPosition.positionF();

    auto newWorldPositionComponent = new WorldPositionComponent(entityId);
    newWorldPositionComponent->x = &position.x();
    newWorldPositionComponent->y = &position.y();

    return newWorldPositionComponent;
}
