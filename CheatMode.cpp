#include "CheatMode.hpp"
#include "../API/Engine/WindowAPI.hpp"
#include "./Components/HealthComponent.hpp"
#include "./Components/Wallet/WalletComponent.hpp"
#include "./Scenes/PoolLevel.hpp"

void CheatMode::render(const Input &i) {
    _windowApi.renderCheatMenu(_isCheatMode);

    if (_windowApi.showCheckBox("God Mode", &_isGodMode)) {
        _characterHealthComponent->isGodMode = !_characterHealthComponent->isGodMode;
    }

    if (_windowApi.showCheckBox("Spawn Zombies (Middle Mouse)", &_spawnZombies)) {
        _poolLevel.spawnPoolOnMiddleClick = _spawnZombies ? &_zombiePool : nullptr;
    }

    if (_windowApi.showCheckBox("Teleport Player (Middle Mouse)", &_teleportPlayer)) {
        _character.cheatMode = _teleportPlayer;
    }

    if (_windowApi.showInputInt("Set Money Player", &_newValue)) {
        _walletComponent->zombytes = _newValue;
    }

    _windowApi.showInputText("", _newLevelValue, 100);
    if (_windowApi.button("Load Level")) {
        try {
            ResourceManager::getInstance()->loadResource(std::string(_newLevelValue));
        }
        catch (std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }

    _windowApi.clearCheatMenu();
}

CheatMode::CheatMode(WindowAPI &windowApi, bool *isCheatMode)
        : _windowApi(windowApi),
          _isCheatMode(*isCheatMode),
          _poolLevel(*Game::getInstance()->getPoolLevel()),
          _zombiePool(_poolLevel.getPool("zombie")),
          _character(*Game::getInstance()->getCharacter()) {
    _characterHealthComponent = _character.getComponent<HealthComponent>();
    _walletComponent = _character.getComponent<WalletComponent>();
    _newValue = _walletComponent->zombytes;
}