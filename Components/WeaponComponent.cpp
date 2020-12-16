#include "WeaponComponent.hpp"

#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"
#include <iostream>

void WeaponComponent::render() {

}

void WeaponComponent::update(const Input &inputSystem) {

}

void WeaponComponent::fixedUpdate(const float &deltaTime) {

}

std::string WeaponComponent::name() const {
    return "WeaponComponent";
}

Component *WeaponComponent::clone(EntityId entityId, const Components::component *component) {
    return nullptr;
}

void WeaponComponent::initialize(EntityObject &entityParent) {

}

void WeaponComponent::shoot(const TransformComponent& transform) {
    EntityObject *bullet = _bulletPool.getEntity();
    PhysicsComponent* physicsComponent = bullet->getPhysicsComponent();
    physicsComponent->setEnabled(true);

    Vector2 spawnPos = transform.getPosition() + (transform.right() * 100);


    physicsComponent->setFixedRotation(true);
    physicsComponent->setTransform(spawnPos, transform.rotation);
    physicsComponent->setFixedRotation(false);

    physicsComponent->setVelocity(transform.right() * 100);
}
