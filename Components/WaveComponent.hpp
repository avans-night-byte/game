#pragma once

#include "Component.hpp"
#include "../Object/Pool.hpp"
#include <string>

class WaveComponent : public Component {

private:
    EntityObject* _parent = nullptr;
    float _totalTime = 0;
    float _nextTime = 0.0f;
    float _period = 1;
    void spawnEntity();
    Pool *_spawnPool = nullptr;
    bool _isPaused = false;


public:

    WaveComponent(EntityId entityId);
    std::string _poolName{};

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;
    void postInitialize(EntityObject &entityObject) override;

    void pause();
    void resume();

    float getPeriod();
    void setPeriod(float period);
};
