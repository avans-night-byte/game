#include "WalletComponent.hpp"

WalletComponent::WalletComponent(EntityId id) : Component(id) {}

void WalletComponent::addItemsFromTransaction(TransactionData &data) {
    _experience += data.getExperience();
    _score += data.getScore();
    _zombytes += data.getZombytes();
}

void WalletComponent::addExperience(int experience) {
 _experience += experience;
}

void WalletComponent::addScore(int score) {
    _score += score;
}

void WalletComponent::addZombytes(int zombytes) {
    _zombytes += zombytes;
}

int WalletComponent::getZombytes() const {
    return _zombytes;
}

int WalletComponent::getExperience() const {
    return _experience;
}

int WalletComponent::getScore() const {
    return _score;
}

void WalletComponent::initialize(EntityObject &entityParent) {}

void WalletComponent::render() {}

void WalletComponent::update(const Input &inputSystem) {}

void WalletComponent::fixedUpdate(const float &deltaTime) {}

std::string WalletComponent::name() const {
    return "WalletComponent";
}

Component *WalletComponent::build(EntityId entityId, const Components::component *component) {
    return new WalletComponent(entityId);
}







