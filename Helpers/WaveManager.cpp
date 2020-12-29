//
// Created by sasch on 29/12/2020.
//

#include "WaveManager.hpp"
#include "../Game.hpp"
#include "../Scenes/LevelBase.hpp"
#include "../Components/WaveComponent.hpp"
#include "../Helpers/GameTime.h"
#include <vector>

WaveManager* WaveManager::_instance = nullptr;

WaveManager &WaveManager::getInstance() {
    if(_instance == nullptr){
        _instance = new WaveManager;
    }
    return *_instance;
}

int WaveManager::getWave() const {
    return _wave;
}

void WaveManager::setWave(int wave = 0) {
    if(wave == 0){
        _wave++;
        return;
    }

    _wave = wave;
}

void WaveManager::updateSlaves() {
    Game::getInstance()->getLevel().findComponents<WaveComponent>(_slaves);

    for(auto* slave : _slaves){
        //TODO: Update slave their spawnRate according to the wave, location of the player.
    }
}

void WaveManager::render() {
    //TODO: Render the current wave underneath the rest of the stats.
}

void WaveManager::update() {
    //TODO: Keep track of wave time, pauses.
    float time = GameTime::getInstance().getTotalTimeSeconds();
    if(time > _nextTime){
        if(_isGrace){
            _nextTime = time + _waveTime;
            resumeSlaves();
        }
        else{
            setWave();
            updateSlaves();
            pauseSlaves();
            _nextTime = time + _gracePeriod;
        }
    }
}

void WaveManager::pauseSlaves() {
    _isGrace = true;

    for(auto* slave : _slaves){
        slave->pause();
    }
}

void WaveManager::resumeSlaves() {
    _isGrace = false;
    for(auto* slave : _slaves){
        slave->resume();
    }
}

