#pragma once

#include "../../API/Rendering/RenderingAPI.hpp"

class FrameCounter {
private:
    float _frameCounter = 0;
    float _totalTime = 0;
    int _averageFPS = 0;
    std::chrono::time_point<std::chrono::system_clock>  _currentTime;

    RenderingAPI &_renderingAPI;

public:
    explicit FrameCounter(RenderingAPI &_renderingAPI);
    void render();
};


