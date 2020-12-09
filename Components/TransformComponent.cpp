#include <Generated/components.hxx>
#include "TransformComponent.hpp"

void TransformComponent::refLocation(const float &rX, const float &rY) {
    this->physicsX = &rX;
    this->physicsY = &rY;
}


void TransformComponent::fixedUpdate(const float &deltaTime) {

}

std::string TransformComponent::name() const {
    return "WorldPositionComponent";
}

Component *TransformComponent::clone(EntityId entityId, const Components::component *component) {
    auto &resourceWorldPosition = component->worldPositionComponent().get();
    auto *position = resourceWorldPosition.position()._clone();

    auto newWorldPositionComponent = new TransformComponent(entityId);
    newWorldPositionComponent->refLocation(position->x(), position->y());

    return newWorldPositionComponent;
}

void TransformComponent::render() {

}

void TransformComponent::update(const Input &inputSystem) {

}

void TransformComponent::setRotation(float rotation) {
    this->rotation = rotation;
}

void TransformComponent::setLocation(const float &x, const float &y) {

}
