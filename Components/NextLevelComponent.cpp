//
// Created by husey on 29/11/2020.
//

#include "NextLevelComponent.hpp"
#include "../Game.hpp"

void NextLevelComponent::startContact() {
    // TODO: Hardcoded
  //  Game::setCurrentState(10);
}

std::string NextLevelComponent::name() const {
    return "NextLevelComponent";
}

void NextLevelComponent::endContact() {

}

void NextLevelComponent::update() {

}

Component *NextLevelComponent::Clone(EntityId entityId) const {
    return new NextLevelComponent(entityId);
}