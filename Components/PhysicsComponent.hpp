#pragma once

#include "../../API/Physics/EnginePhysicsAPI.hpp"
#include "Component.hpp"

class PhysicsComponent : public Component {
public:
    string wow = "huseyin";

private:
    const PhysicsAPI *enginePhysicsAPI;
    unsigned int bodyId;

public:
    explicit PhysicsComponent() : Component(), bodyId(0) {

    }

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size);

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius);

    unique_ptr<Component> Clone(EntityId entityId) override;

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




