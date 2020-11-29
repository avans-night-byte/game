//
// Created by husey on 29/11/2020.
//

#include "NextLevelComponent.hpp"
#include "../Game.hpp"

void NextLevelComponent::startContact() {
    cout << "HOLY FUCK MOTHERFUCKER" << endl;
    // TODO: Hardcoded
    Game::SetCurrentState(10);
}

void NextLevelComponent::endContact() {

}
