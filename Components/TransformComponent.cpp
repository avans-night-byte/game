#include <Generated/components.hxx>
#include "TransformComponent.hpp"
#include "EntityObject.hpp"

void TransformComponent::refLocation(const float &rX, const float &rY) {
    this->physicsX = &rX;
    this->physicsY = &rY;
}


void TransformComponent::fixedUpdate(const float &deltaTime) {

}

std::string TransformComponent::name() const {
    return "TransformComponent";
}

Component *TransformComponent::clone(EntityId entityId, const Components::component *component) {
    auto &resourceWorldPosition = component->transformComponent().get();
    auto *position = resourceWorldPosition.position()._clone();

    auto newWorldPositionComponent = new TransformComponent(entityId);
    newWorldPositionComponent->refLocation(position->x(), position->y());

    return newWorldPositionComponent;
}

void TransformComponent::render() {

}

void TransformComponent::update(const Input &inputSystem) {

}

void TransformComponent::setRotation(float r) {
    this->rotation = r;
}

void TransformComponent::initialize(EntityObject &entityParent) {

}
