#pragma once

class WindowAPI;
class HealthComponent;

class CheatMode {
private:
    const WindowAPI &_windowApi;
    bool &_isCheatMode;

    HealthComponent *_characterHealthComponent = nullptr;

    bool isGodMode = false;

public:
    CheatMode(WindowAPI &windowApi, bool *isCheatMode);

    void render();
};
