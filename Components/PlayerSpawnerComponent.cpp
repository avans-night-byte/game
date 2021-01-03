#include "PlayerSpawnerComponent.hpp"
#include "EntityObject.hpp"

#include "Generated/components.hxx"

#include <string>



void PlayerSpawnerComponent::render() {

}

void PlayerSpawnerComponent::update(const Input &inputSystem) {

}

void PlayerSpawnerComponent::fixedUpdate(const float &deltaTime) {

}

std::string PlayerSpawnerComponent::name() const {
    return "PlayerSpawnerComponent";
}

Component *PlayerSpawnerComponent::build(EntityId entityId, const Components::component *component) {
    auto &xml = component->playerSpawnerComponent().get();

    auto *playerSpawnerComponent = new PlayerSpawnerComponent(entityId);
    playerSpawnerComponent->_pointName = xml.pointName();

    return playerSpawnerComponent;
}

void PlayerSpawnerComponent::initialize(EntityObject &entityParent) {
    _transformComponent = entityParent.getTransform();
}

void PlayerSpawnerComponent::postInitialize(EntityObject &entityObject) {

}

PlayerSpawnerComponent::PlayerSpawnerComponent(EntityId i) : Component(i) {

}
