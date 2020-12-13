#pragma once

#include "../../API/Rendering/RenderingAPI.hpp"
#include "../Helpers/GameTime.h"

class FrameCounter {
private:

    float _frameCounter = 0;
    int _averageFPS = 0;

    GameTime &_gameTime;
    RenderingAPI &_renderingAPI;

public:
    explicit FrameCounter(RenderingAPI &_renderingAPI);
    void render();
};


