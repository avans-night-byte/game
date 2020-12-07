#pragma once

#include "../../API/Physics/EnginePhysicsAPI.hpp"
#include "../../API/RPosition.hpp"
#include "Component.hpp"

class PhysicsComponent : public Component {
private:
    const PhysicsAPI *enginePhysicsAPI;
    unsigned int bodyId = 0;

    std::string contactHandlerName;

public:
    inline const std::string& getContactHandlerName() {
        return contactHandlerName;
    }


    void setContactHandler(Component *pComponent);

public:
    explicit PhysicsComponent(EntityId id);

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size);

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius);

    ~PhysicsComponent() override {
        // BodyId 0 is used for physicsComponent that are not instantiated within the b2World.
        if(bodyId == 0)
            return;

        enginePhysicsAPI->destroyBody(bodyId);
    }

    inline RPosition getRPosition() {
        return enginePhysicsAPI->getRPosition(bodyId);
    }

    inline void getVelocity(Vector2 &velocity) {
        enginePhysicsAPI->GetVelocity(velocity, bodyId);
    }

    inline void setVelocity(const Vector2 &velocity) {
        enginePhysicsAPI->setLinearVelocity(bodyId, velocity);
    }

    inline void setFixedRotation(bool value) {
        enginePhysicsAPI->setFixedRotation(bodyId, value);
    }

    static inline BodyType StringToBodyType(const std::string& value)
    {
        if(value == "Dynamic") return BodyType::Dynamic;
        if(value == "Static") return BodyType::Static;
        if(value == "Kinematic") return BodyType::Kinematic;

        throw std::runtime_error("BodyType Value: " + value + " could not be parsed.");
    }

public:
    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    void update() override;

    [[nodiscard]] Component *Clone(EntityId entityId, const LevelResources::component *component) override;

private:
    inline BodyId initializeBoxBody(BodyType bodyType, Vector2 position, Vector2 size) {
        Box2DBoxData box2DBoxData;
        box2DBoxData.bodyType = bodyType;
        box2DBoxData.position = position;
        box2DBoxData.size = size;
        return enginePhysicsAPI->createStaticBody(box2DBoxData);
    }

    inline BodyId initializeCircleBody(BodyType bodyType, Vector2 position, float radius) {
        Box2DCircleData box2DBoxData;
        box2DBoxData.bodyType = bodyType;
        box2DBoxData.position = position;
        box2DBoxData.radius = radius;
        return enginePhysicsAPI->createStaticBody(box2DBoxData);
    }
};




