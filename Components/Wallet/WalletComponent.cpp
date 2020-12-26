#include "WalletComponent.hpp"
#include "../../Game.hpp"

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

void WalletComponent::initialize(EntityObject &entityParent) {
    _renderAPI = &Game::getInstance()->getRenderingApi();
}

void WalletComponent::render() {

    std::string exp = "exp_" + std::to_string(_experience);
    std::string zombytes = "zomb_" + std::to_string(_zombytes);
    std::string score = "sc_" + std::to_string(_score);

    if(_walletText[exp] == nullptr){
        auto wrapper = TextWrapper::createText(*_renderAPI, "EXP: " + std::to_string(_experience), "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", exp);
        _walletText[exp] = wrapper;
    }

    if(_walletText[zombytes] == nullptr){
        auto wrapper = TextWrapper::createText(*_renderAPI, "Z: " + std::to_string(_zombytes), "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", zombytes);
        _walletText[zombytes] = wrapper;
    }

    if(_walletText[score] == nullptr){
        auto wrapper = TextWrapper::createText(*_renderAPI, "SCORE: " + std::to_string(_score), "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", score);
        _walletText[score] = wrapper;
    }

    _walletText[exp]->render(550, 50);
    _walletText[zombytes]->render(550, 70);
    _walletText[score]->render(550, 90);

}

void WalletComponent::update(const Input &inputSystem) {}

void WalletComponent::fixedUpdate(const float &deltaTime) {}

std::string WalletComponent::name() const {
    return "WalletComponent";
}

Component *WalletComponent::build(EntityId entityId, const Components::component *component) {
    return new WalletComponent(entityId);
}







