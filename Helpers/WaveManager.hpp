#pragma once
#include "../Components/WaveComponent.hpp"
#include "../../Engine/Rendering/TextWrapper.hpp"
#include <vector>
class WaveManager {
    private:
        static WaveManager *_instance;

        std::map<std::string, TextWrapper*> _waveText {};
        RenderingAPI *_renderingAPI = nullptr;

    int _wave = 1;
        std::vector<WaveComponent*> _slaves{};

        // Tracking next wave;
        float _nextTime = 0.0f;

        // Wave time in seconds, this gets multiplied every round.
        float _waveTime = 10.0f;
        float _gracePeriod = 5.0f;
        bool _isGrace = false;

    public:
        WaveManager();
        static WaveManager& getInstance();
        int getWave() const;
        void setWave(const int wave);
        void updateSlaves();
        void updateMaster();
        void pauseSlaves();
        void resumeSlaves();
        void render();
        void update();
};