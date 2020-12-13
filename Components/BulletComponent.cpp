#include "BulletComponent.hpp"

#include "EntityObject.hpp"
#include "PhysicsComponent.hpp"
#include "TransformComponent.hpp"

#include <string>

void BulletComponent::render() {

}

void BulletComponent::update(const Input &inputSystem) {

}

void BulletComponent::fixedUpdate(const float &deltaTime) {


}

std::string BulletComponent::name() const {
    return "BulletComponent";
}

Component *BulletComponent::clone(EntityId entityId, const Components::component *component) {
    return new BulletComponent(entityId);
}

void BulletComponent::initialize(EntityObject &entityParent) {
}
