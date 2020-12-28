#include "NextLevelComponent.hpp"
#include "../../Engine/Managers/ResourceManager.hpp"

#include "./EntityObject.hpp"
#include "Characters/CharacterComponent.hpp"

std::string NextLevelComponent::name() const {
    return "NextLevelComponent";
}

void NextLevelComponent::fixedUpdate(const float &deltaTime) {

}

Component *NextLevelComponent::build(EntityId entityId, const Components::component *component) {
    const auto &nextLevelComponent = component->nextLevelComponent();
    auto *newInstance = new NextLevelComponent(entityId);
    newInstance->NextLevel = nextLevelComponent->levelName();
    return newInstance;
}

void NextLevelComponent::render() {

}

void NextLevelComponent::update(const Input &inputSystem) {
    if (hasContactWithPlayer) {
        if (_playerSpawnerComponent) {
            Game::getInstance()->currentSpawner = _playerSpawnerComponent;
        }
        ResourceManager::getInstance()->loadResource(NextLevel);
    }
}

void NextLevelComponent::initialize(EntityObject &entityParent) {
}

void NextLevelComponent::onCollisionEnter(EntityObject *self, EntityObject *other) {
    if (auto *characterComponent = other->getComponent<CharacterComponent>()) {
        hasContactWithPlayer = true;
    }
}

void NextLevelComponent::onCollisionExit(EntityObject *self, EntityObject *other) {
    if (auto *characterComponent = other->getComponent<CharacterComponent>()) {
        hasContactWithPlayer = false;
    }
}

void NextLevelComponent::postInitialize(EntityObject &entityObject) {

}
