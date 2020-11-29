//
// Created by husey on 29/11/2020.
//

#include "NextLevelComponent.hpp"
#include "../Game.hpp"

void NextLevelComponent::startContact() {
    // TODO: Hardcoded
    Game::setCurrentState(10);
}

void NextLevelComponent::endContact() {

}
