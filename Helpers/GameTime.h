#pragma once

#include <chrono>
#include "../../API/Helpers/Event.h"

class GameTime {
private:

    float _totalTime{};

    float _totalTimeSeconds{};

    float _frameTimeSeconds{};
    float _frameTimeMiliSeconds{};

    float _deltaTime = 1 / 60.0;
    float _time = 0;
    float _accumulator = 0.0f;
    float _multiplier = 1;

    std::chrono::time_point<std::chrono::system_clock> _currentTime;

    static GameTime *_instance;
    Event<float> _fixedUpdateEventHandler;

public:
    static GameTime &getInstance();

    GameTime();

    void update();

    [[nodiscard]] float getTime() const;

    [[nodiscard]] float getDeltaTime() const;

    [[nodiscard]] float getTotalTime() const;

    [[nodiscard]] float getAccumulator() const;

    [[nodiscard]] float getFrameTimeSeconds() const;

    [[nodiscard]] float getFrameTimeMiliSeconds() const;
    void increaseMultiplier();
    void decreaseMultiplier();

public:
    void resetTotalTime();

    void setAccumulator(float value);

    void setDeltaTime(float value);

    void setTime(float value);

public:

    Event<float> &getFixedUpdateEvent();

    float getTotalTimeSeconds() const;
};


