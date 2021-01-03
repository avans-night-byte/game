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

WaveManager &WaveManager::getInstance(bool reset) {
    if(_instance == nullptr || reset){
        _instance = new WaveManager();
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
    _slaves.clear();
    Game::getInstance()->getLevel().findComponents<WaveComponent>(_slaves);
    float spawnRate = 3;
    spawnRate -= (_wave * 0.3f);

    for(auto* slave : _slaves){
        slave->setPeriod(spawnRate);
    }
}

void WaveManager::render() {
    const std::string wave = "wv_wave_" + std::to_string(_wave);

    if(_waveText[wave] == nullptr){
        _waveText.clear();

        auto wrapper = TextWrapper::createText(*_renderingAPI, "WAVE: " + std::to_string(_wave), "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", wave);
        _waveText[wave] = wrapper;
    }

    _waveText[wave]->render(550, 110);

}

void WaveManager::update() {
    if(_slaves.empty()){
        return;
    }

    //TODO: Keep track of wave time, pauses.
    float time = GameTime::getInstance().getTotalTimeSeconds();
    if(time > _nextTime){
        if(_isGrace || _nextTime == 0){
            _nextTime = time + _waveTime;
            resumeSlaves();
        }
        else{
            setWave();
            updateMaster();
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

void WaveManager::updateMaster() {
    _waveTime += 2;
    _gracePeriod += 1;
}

WaveManager::WaveManager() {
    _renderingAPI = &Game::getInstance()->getRenderingAPI();
}

void WaveManager::levelUpdate() {
    updateSlaves();
    if(_isGrace){
        pauseSlaves();
    }
}

