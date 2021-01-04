#include "HealthComponent.hpp"
#include "../Save/SaveSystem.hpp"

#include <iostream>
#include <filesystem>
#include "Wallet/WalletComponent.hpp"

float HealthComponent::getHealth() const {
    return this->_healthPoints;
}

void HealthComponent::setHealth(float newHealthPoints) {
    this->_healthPoints = newHealthPoints;
}

void HealthComponent::doDamage(float amountOfHealthPoints) {
    if(isGodMode)
        return;

    std::cout << "HealthComponent: Damaged from " << this->getHealth() << " to " << this->_healthPoints << std::endl;

    float newHealth = this->_healthPoints -= amountOfHealthPoints;

    if (newHealth <= 0) {
        this->die();
    } else {
        this->setHealth(newHealth);
    }
}

void HealthComponent::die() {
    std::cout << "HealthComponent: You died" << std::endl;
    this->setHealth(0);
    ResourceManager::getInstance()->quitLevel = true;
    ResourceManager::getInstance()->loadResource("GameOver");

    SaveSystem::saveSave("../../Resources/Saves/save.xml", "");
    SaveSystem::saveHighscore("../../Resources/Saves/save.xml");

    std::vector<int> scores = SaveSystem::getHighscores();

    MenuParser::getInstance()->setDynamicFieldValue("%score%", "Your score: " + std::to_string(Game::getInstance()->getCharacter()->getComponent<WalletComponent>()->getScore()));
    MenuParser::getInstance()->setDynamicFieldValue("%highscore_1%", "1. " + std::to_string(scores[0]));
    MenuParser::getInstance()->setDynamicFieldValue("%highscore_2%", "2. " + std::to_string(scores[1]));
    MenuParser::getInstance()->setDynamicFieldValue("%highscore_3%", "3. " + std::to_string(scores[2]));
    MenuParser::getInstance()->setDynamicFieldValue("%highscore_4%", "4. " + std::to_string(scores[3]));
    MenuParser::getInstance()->setDynamicFieldValue("%highscore_5%", "5. " + std::to_string(scores[4]));

    // Reset the game on death.
    SaveSystem::clearSave();
    this->setHealth(100);
    Game::getInstance()->getCharacter()->getComponent<WalletComponent>()->reset();
}

void HealthComponent::render() {
    Vector2 vec1(10, 50);
    Vector2 vec2(20, 60);
    std::string color("000000");
    std::string colo2("ff1100");
    _renderingApi.drawRectangle(vec1, 500, 50, color, 255);
    _renderingApi.drawRectangle(vec2,  480.f / 100.f * _healthPoints, 30, colo2, 255);
}


void HealthComponent::update(const Input &inputSystem) {
    if (inputSystem.keyMap.type == KeyType::KeyUp) {
        _damageIsDone = false;
    } else if (!_damageIsDone && inputSystem.keyMap.code == "G") {
        doDamage(10);
        _damageIsDone = true;
    }
}

void HealthComponent::fixedUpdate(const float &deltaTime) {

}

std::string HealthComponent::name() const {
    return "HealthComponent";
}

Component *HealthComponent::build(EntityId entityId, const Components::component *component) {
    return new HealthComponent(entityId);
}

void HealthComponent::initialize(EntityObject &entityParent) {

}

void HealthComponent::postInitialize(EntityObject &entityObject) {

}
