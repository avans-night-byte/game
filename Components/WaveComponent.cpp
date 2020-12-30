//
// Created by sasch on 29/12/2020.
//

#include "WaveComponent.hpp"
#include "../Game.hpp"
#include "../Helpers/GameTime.h"
#include <string>
#include "../Scenes/PoolLevel.hpp"
#include "./TransformComponent.hpp"

void WaveComponent::render() {

}

WaveComponent::WaveComponent(EntityId  entityId){

}
void WaveComponent::update(const Input &inputSystem) {
    //TODO: Spawn something every x time.
    float time = GameTime::getInstance().getTotalTimeSeconds();

    if(_isPaused)
        return;

    if(time > _nextTime){
        _nextTime = time + _period;

        spawnEntity();
    }
}

void WaveComponent::fixedUpdate(const float &deltaTime) {
}

std::string WaveComponent::name() const {
    return "WaveComponent";
}

Component *WaveComponent::build(EntityId entityId, const Components::component *component) {
    auto newWaveComponent = new WaveComponent(entityId);
    auto &waveComponent = component->WaveComponent().get();


    newWaveComponent->_poolName = waveComponent.poolName();
    return newWaveComponent;
}

void WaveComponent::initialize(EntityObject &entityParent) {
    _parent = &entityParent;
    _spawnPool = &Game::getInstance()->getPoolLevel()->getPool(_poolName);
}

void WaveComponent::postInitialize(EntityObject &entityObject) {
}


/**
 * Spawns an entity from the specified pool in the xml.
 */
void WaveComponent::spawnEntity() {
    auto parentTransform = _parent->getTransform();
    auto spawnPosition = Vector2{parentTransform->getPosition().x, parentTransform->getPosition().y};

    // Create Entity.

    EntityObject &obj = _spawnPool->getEntity();
    auto *physicsComponent = obj.getComponent<PhysicsComponent>();

    if (physicsComponent) {
        Vector2 spawnPos = spawnPosition;

        physicsComponent->setTransform(spawnPos, 0);
        Game::getInstance()->addEventBodyHandler([physicsComponent] {
            physicsComponent->setEnabled(true);
        });
    }
}

void WaveComponent::pause() {
    _isPaused = true;
}

void WaveComponent::resume() {
    _isPaused = false;
}

float WaveComponent::getPeriod() {
    return _period;
}

void WaveComponent::setPeriod(float period) {
    _period = period;
}
