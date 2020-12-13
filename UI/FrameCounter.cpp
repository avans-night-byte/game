
#include <chrono>
#include "FrameCounter.h"

void FrameCounter::render(){

    auto newTime = std::chrono::high_resolution_clock::now();
    float frameTimeSeconds = std::chrono::duration_cast<std::chrono::microseconds>(newTime - _currentTime).count() / 1000000.0f;

    _currentTime = newTime;
    _totalTime += frameTimeSeconds;
    
    _frameCounter++;
    // The total frames in the last second are fps.
    if (_totalTime >= 1.0f) {
        _averageFPS = _frameCounter;

        _frameCounter = 0;
        _totalTime = 0;

        _renderingAPI.createText("../../Resources/Fonts/LiberationMono-Regular.ttf",
                                  std::to_string(_averageFPS),
                                  25,
                                  "ffffff", "fpsText");
    }

    _renderingAPI.drawTexture("fpsText", 0, 0, 0, 0, 1, 0);
}

FrameCounter::FrameCounter(RenderingAPI &_renderingAPI) : _renderingAPI(_renderingAPI) {
    _currentTime = std::chrono::high_resolution_clock::now();
}
