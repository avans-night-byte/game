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
              bodyId{this->initializeBoxBody(bodyType, position, size)} {

    }

    explicit PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius)
            : Component(id),
              enginePhysicsAPI(Game::getInstance()->getPhysicsAPI()),
              bodyId(this->initializeCircleBody(bodyType, position, radius)) {
    }

    ~PhysicsComponent(){
        enginePhysicsAPI->destroyBody(bodyId);
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

    inline void setAngle(float angle){
        enginePhysicsAPI->setAngle(bodyId, angle);
    }

    inline void setFixedRotation(bool value)
    {
        enginePhysicsAPI->setFixedRotation(bodyId, value);
    }

    void update() override;

private:
    inline BodyId initializeBoxBody(BodyType bodyType, Vector2 position, Vector2 size)
    {
        Box2DBoxData box2DBoxData;
        box2DBoxData.bodyType = bodyType;
        box2DBoxData.position = position;
        box2DBoxData.size = size;
        return enginePhysicsAPI->createStaticBody(box2DBoxData);
    }

    inline BodyId initializeCircleBody(BodyType bodyType, Vector2 position, float radius)
    {
        Box2DCircleData box2DBoxData;
        box2DBoxData.bodyType = bodyType;
        box2DBoxData.position = position;
        box2DBoxData.radius = radius;
        return enginePhysicsAPI->createStaticBody(box2DBoxData);
    }
};




