#include "BulletComponent.hpp"

#include "EntityObject.hpp"
#include "PhysicsComponent.hpp"
#include "TransformComponent.hpp"
#include "Characters/ZombieComponent.hpp"
#include "../Game.hpp"

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

Component *BulletComponent::build(EntityId entityId, const Components::component *component) {
    return new BulletComponent(entityId);
}

void BulletComponent::initialize(EntityObject &entityParent) {
    entityParent.getComponent<PhysicsComponent>()->collisionHandlers.push_back(this);
}

void BulletComponent::onCollisionEnter(EntityObject *self, EntityObject *other) {
    Game::getInstance()->addEventBodyHandler(
            [self] {
                self->destroy();
            }
    );
}

void BulletComponent::onCollisionExit(EntityObject *self, EntityObject *other) {

}

void BulletComponent::postInitialize(EntityObject &entityObject) {

}
