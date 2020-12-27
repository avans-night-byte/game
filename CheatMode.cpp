#include "CheatMode.hpp"
#include "../API/Engine/WindowAPI.hpp"
#include "./Components/HealthComponent.hpp"

void CheatMode::render() {
    _windowApi.renderCheatMenu(_isCheatMode);

    if (_windowApi.showCheckBox("God Mode", &isGodMode)) {
        _characterHealthComponent->isGodMode = !_characterHealthComponent->isGodMode;
    }

    _windowApi.clearCheatMenu();
}

CheatMode::CheatMode(WindowAPI &windowApi, bool *isCheatMode) : _windowApi(windowApi), _isCheatMode(*isCheatMode) {
    EntityObject *_characterObject = Game::getInstance()->getCharacter();

    _characterHealthComponent = _characterObject->getComponent<HealthComponent>();
}