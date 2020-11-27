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

    void update() override;
};




