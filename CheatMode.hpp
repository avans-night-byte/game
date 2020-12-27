#pragma once

#include "../Engine/Input/Input.hpp"

class WindowAPI;

class Pool;

class EntityObject;

class PoolLevel;

class HealthComponent;

class WalletComponent;

class CheatMode {
private:
    const WindowAPI &_windowApi;
    bool &_isCheatMode;


    HealthComponent *_characterHealthComponent;
    WalletComponent *_walletComponent;
    EntityObject &_character;
    PoolLevel &_poolLevel;
    Pool &_zombiePool;

    bool _isGodMode = false;
    bool _spawnZombies = false;
    bool _teleportPlayer = false;
    int _newValue = 0;
    char _newLevelValue[100] = "";

public:
    CheatMode(WindowAPI &windowApi, bool *isCheatMode);

    void render(const Input &i);
};
