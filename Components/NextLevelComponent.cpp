#include <b2_contact.h>
#include "NextLevelComponent.hpp"
#include "../../Engine/Managers/ResourceManager.hpp"

#include "../Components/EntityObject.hpp"
#include "../Game.hpp"

//void NextLevelComponent::startContact(b2Contact *contact) {
//    if (auto *characterComponent = static_cast<CharacterComponent *>((CharacterComponent *) contact->GetFixtureB()->GetBody()->GetUserData().pointer)) {
//        hasContactWithPlayer = true;
//    }
//}

std::string NextLevelComponent::name() const {
    return "NextLevelComponent";
}

//void NextLevelComponent::endContact(b2Contact *contact) {
//    if (auto *characterComponent = static_cast<CharacterComponent *>((CharacterComponent *) contact->GetFixtureB()->GetBody()->GetUserData().pointer)) {
//        hasContactWithPlayer = false;
//    }
//}

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
    if (inputSystem.keyMap.action == "INTERACT" && hasContactWithPlayer) {
        ResourceManager::getInstance()->loadResource(NextLevel);
    }
}

void NextLevelComponent::initialize(EntityObject &entityParent) {

}

void NextLevelComponent::onCollisionEnter(EntityObject *entityObject) {

}

void NextLevelComponent::onCollisionExit(EntityObject *entityObject) {

}
