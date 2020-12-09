#include <Generated/components.hxx>
#include "WorldPositionComponent.hpp"

void WorldPositionComponent::refLocation(const float &rX, const float &rY) {
    this->physicsX = &rX;
    this->physicsY = &rY;
}


void WorldPositionComponent::fixedUpdate(const float &deltaTime) {

}

std::string WorldPositionComponent::name() const {
    return "WorldPositionComponent";
}

Component *WorldPositionComponent::clone(EntityId entityId, const Components::component *component) {
    auto &resourceWorldPosition = component->worldPositionComponent().get();
    auto *position = resourceWorldPosition.position()._clone();

    auto newWorldPositionComponent = new WorldPositionComponent(entityId);
    newWorldPositionComponent->refLocation(position->x(), position->y());

    return newWorldPositionComponent;
}

void WorldPositionComponent::render() {

}

void WorldPositionComponent::update(const Input &inputSystem) {

}
