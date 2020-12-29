#pragma once
#include "../Components/WaveComponent.hpp"
#include <vector>
class WaveManager {
    private:
        static WaveManager *_instance;
        int _wave = 1;
        std::vector<WaveComponent*> _slaves{};

        // Tracking next wave;
        float _nextTime = 0.0f;

        // Wave time in seconds, this gets multiplied every round.
        float _waveTime = 30.0f;
        float _gracePeriod = 15.0f;

        bool _isGrace = false;

    public:
        static WaveManager& getInstance();
        int getWave() const;
        void setWave(const int wave);
        void updateSlaves();
        void pauseSlaves();
        void resumeSlaves();
        void render();
        void update();
};