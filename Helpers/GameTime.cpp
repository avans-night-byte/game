#include "GameTime.h"

GameTime &GameTime::getInstance() {
    if(_instance == nullptr){
        _instance = new GameTime;
    }
    return *_instance;
}

GameTime *GameTime::_instance;

GameTime::GameTime() {
    _currentTime = std::chrono::high_resolution_clock::now();
}

void GameTime::update() {
    auto newTime = std::chrono::high_resolution_clock::now();
    _frameTimeSeconds = std::chrono::duration_cast<std::chrono::microseconds>(newTime - _currentTime).count() / 1000000.0f;
    _frameTimeMiliSeconds = std::chrono::duration_cast<std::chrono::microseconds>(newTime - _currentTime).count() / 100000.0f;

    _currentTime = newTime;
    _accumulator += _frameTimeMiliSeconds;
    _totalTime += _frameTimeSeconds;

    _totalTimeSeconds += _frameTimeSeconds;

    while (_accumulator >= _deltaTime) {
        _fixedUpdateEventHandler(_deltaTime * _multiplier);

        _time += _deltaTime;
        _accumulator -= _deltaTime;
    }
}

float GameTime::getTime() const {
    return _time;
}

float GameTime::getDeltaTime() const {
    return _deltaTime;
}

float GameTime::getTotalTime() const {
    return _totalTime;
}

float GameTime::getFrameTimeSeconds() const {
    return _frameTimeSeconds;
}
float GameTime::getFrameTimeMiliSeconds() const{
    return _frameTimeMiliSeconds;
}

float GameTime::getAccumulator() const {
    return _accumulator;
}

float GameTime::getTotalTimeSeconds() const {
    return _totalTimeSeconds;
}

void GameTime::resetTotalTime() {
    _totalTime = 0;
}

Event<float> &GameTime::getFixedUpdateEvent(){
    return _fixedUpdateEventHandler;
}

void GameTime::setAccumulator(float value) {
    _accumulator = value;
}

void GameTime::setDeltaTime(float value) {
    _deltaTime = value;
}

void GameTime::setTime(float value) {
    _time = value;
}

void GameTime::increaseMultiplier() {
    _multiplier = _multiplier + .1f;
}

void GameTime::decreaseMultiplier() {
    if(_multiplier > .1f)
        _multiplier = _multiplier - .1f;
}

