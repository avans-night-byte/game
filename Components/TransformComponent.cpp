#include "TransformComponent.hpp"

void TransformComponent::setLocation(const float& x, const float& y) {
    this->x = &x;
    this->y = &y;
}

void TransformComponent::setRotation(float rotation){
    this->rotation = rotation;
}

void TransformComponent::update() {}