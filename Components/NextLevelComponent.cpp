#include "NextLevelComponent.hpp"

void NextLevelComponent::startContact() {
    // TODO: Hardcoded
  //  Game::setCurrentState(10);
}

std::string NextLevelComponent::name() const {
    return "NextLevelComponent";
}

void NextLevelComponent::endContact() {

}

void NextLevelComponent::fixedUpdate(const float &deltaTime) {

}

Component *NextLevelComponent::clone(EntityId entityId, const Components::component *component) {
    return new NextLevelComponent(entityId);
}

void NextLevelComponent::render() {

}

void NextLevelComponent::update(const Input &inputSystem) {

}
