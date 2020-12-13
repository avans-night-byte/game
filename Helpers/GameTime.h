#pragma once

#include <chrono>
#include "../../Engine/Helpers/Event.h"

class GameTime {
private:

    float _totalTime{};

    float _frameTimeSeconds{};
    float _frameTimeMiliSeconds{};

    float _deltaTime = 1 / 60.0;
    float _time = 0;
    float _accumulator = 0.0f;

    std::chrono::time_point<std::chrono::system_clock> _currentTime;

    Event<float> _fixedUpdateEventHandler;

    static GameTime *_instance;
public:
    static GameTime &getInstance();

    GameTime();

    void update();

    float getTime() const;

    float getDeltaTime() const;

    float getTotalTime() const;

    float getFrameTimeSeconds() const;

    float getFrameTimeMiliSeconds() const;

    Event<float> &getFixedUpdateEvent();

public:
    void resetTotalTime();

};


