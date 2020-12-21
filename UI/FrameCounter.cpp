
#include <chrono>
#include "FrameCounter.h"

void FrameCounter::render(){
    _frameCounter++;
    // The total frames in the last second are fps.
    if (_gameTime.getTotalTime() >= 1.0f) {
        _averageFPS = _frameCounter;

        _frameCounter = 0;
        _gameTime.resetTotalTime();

        _renderingAPI.createText("../../Resources/Fonts/LiberationMono-Regular.ttf",
                                  std::to_string(_averageFPS),
                                  25,
                                  "ffffff", "fpsText");
    }

    _renderingAPI.drawTexture("fpsText", 0, 0, 0, 0, 1, 0);
}

FrameCounter::FrameCounter(RenderingAPI &_renderingAPI): _renderingAPI(_renderingAPI), _gameTime(GameTime::getInstance()) {}
