#pragma once

#include "Component.hpp"
#include "../../API/Physics/EnginePhysicsAPI.hpp"
#include "../Game.hpp"

class PhysicsComponent : public Component {
private:
    const PhysicsAPI *enginePhysicsAPI;
    const unsigned int bodyId;

public:
    explicit PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size)
            : Component(id),
              enginePhysicsAPI(Game::getInstance()->getPhysicsAPI()),
              bodyId(enginePhysicsAPI->createStaticBody(bodyType, position, size)) {
    }

    explicit PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius)
            : Component(id),
              enginePhysicsAPI(Game::getInstance()->getPhysicsAPI()),
              bodyId(enginePhysicsAPI->createStaticBody(bodyType, position, radius)) {
    }

    inline RPosition getRPosition() {
        return enginePhysicsAPI->getRPosition(bodyId);
    }

    inline void getVelocity(Vector2& velocity) {
        enginePhysicsAPI->GetVelocity(velocity, bodyId);
    }

    inline void setVelocity(const Vector2& velocity) {
        enginePhysicsAPI->setLinearVelocity(bodyId, velocity);
    }

    inline void setFixedRotation(bool value)
    {
        enginePhysicsAPI->setFixedRotation(bodyId, value);
    }

    void update() override;
};




