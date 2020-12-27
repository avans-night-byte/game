#include "CheatMode.hpp"
#include "../API/Engine/WindowAPI.hpp"
#include "./Components/HealthComponent.hpp"
#include "./Scenes/PoolLevel.hpp"

void CheatMode::render() {
    _windowApi.renderCheatMenu(_isCheatMode);

    if (_windowApi.showCheckBox("God Mode", &_isGodMode)) {
        _characterHealthComponent->isGodMode = !_characterHealthComponent->isGodMode;
    }

    if (_windowApi.showCheckBox("Spawn Zombies", &_spawnZombies)) {
        _poolLevel.spawnPoolOnMiddleClick = _spawnZombies ? &_zombiePool : nullptr;
    }

    _windowApi.clearCheatMenu();
}

CheatMode::CheatMode(WindowAPI &windowApi, bool *isCheatMode)
        : _windowApi(windowApi),
          _isCheatMode(*isCheatMode),
          _poolLevel(*Game::getInstance()->getPoolLevel()),
          _zombiePool(_poolLevel.getPool("zombie")) {
    EntityObject *_characterObject = Game::getInstance()->getCharacter();

    _characterHealthComponent = _characterObject->getComponent<HealthComponent>();
}