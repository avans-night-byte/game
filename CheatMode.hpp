#pragma once

class WindowAPI;

class Pool;

class PoolLevel;

class HealthComponent;

class CheatMode {
private:
    const WindowAPI &_windowApi;
    bool &_isCheatMode;

    HealthComponent *_characterHealthComponent = nullptr;
    PoolLevel &_poolLevel;
    Pool &_zombiePool;

    bool _isGodMode = false;
    bool _spawnZombies = false;

public:
    CheatMode(WindowAPI &windowApi, bool *isCheatMode);

    void render();
};
