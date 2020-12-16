#include <Generated/components.hxx>
#include "TransformComponent.hpp"
#include "EntityObject.hpp"

void TransformComponent::refLocation(const float &rX, const float &rY) {
    this->_physicsX = &rX;
    this->_physicsY = &rY;
}


void TransformComponent::fixedUpdate(const float &deltaTime) {

}

std::string TransformComponent::name() const {
    return "TransformComponent";
}

Component *TransformComponent::clone(EntityId entityId, const Components::component *component) {
    auto newTransformComponent = new TransformComponent(entityId);

    if (component != nullptr) {
        auto &resourceTransform = component->transformComponent().get();
        auto *position = resourceTransform.position()._clone();

        newTransformComponent->refLocation(position->x(), position->y());
    } else {
        newTransformComponent->refLocation(0, 0);
    }

    return newTransformComponent;
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

TransformComponent &TransformComponent::operator=(Vector2 &v2) {
    this->_x = v2.x;
    this->_y = v2.y;

    return *this;
}
