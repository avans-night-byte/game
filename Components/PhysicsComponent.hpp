#pragma once

#include "../../API/Physics/EnginePhysicsAPI.hpp"
#include "../../API/RPosition.hpp"
#include "Component.hpp"

namespace LevelResources {
    class physicsComponent;
}

class PhysicsComponent : public Component, public ContactHandler {
private:
    const PhysicsAPI *physicsAPI;
    unsigned int bodyId = 0;

    std::string contactHandlerName;

public:
    inline const std::string& getContactHandlerName() {
        return contactHandlerName;
    }

public:
    std::vector<ContactHandler*> contactHandlers{};

    explicit PhysicsComponent(EntityId id);

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size);

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius);

    ~PhysicsComponent() override {
        // BodyId 0 is used for physicsComponent that are not instantiated within the b2World.
        if(bodyId == 0)
            return;

        physicsAPI->destroyBody(bodyId);
    }

    inline RPosition getRPosition() {
        return physicsAPI->getRPosition(bodyId);
    }

    inline void getVelocity(Vector2 &velocity) {
        physicsAPI->GetVelocity(velocity, bodyId);
    }

    inline void setVelocity(const Vector2 &velocity) {
        physicsAPI->setLinearVelocity(bodyId, velocity);
    }

    inline void setFixedRotation(bool value) {
        physicsAPI->setFixedRotation(bodyId, value);
    }

    static inline BodyType StringToBodyType(const std::string& value)
    {
        if(value == "Dynamic") return BodyType::Dynamic;
        if(value == "Static") return BodyType::Static;
        if(value == "Kinematic") return BodyType::Kinematic;

        throw std::runtime_error("BodyType Value: " + value + " could not be parsed.");
    }

public:
    [[nodiscard]] std::string name() const override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    void fixedUpdate(const float &deltaTime) override;

    void render() override;

    void update(const Input &inputSystem) override;

    void startContact() override;

    void endContact() override;

    void setAngle(float angle);

private:
    inline BodyId initializeBoxBody(BodyType bodyType, Vector2 position, Vector2 size) {
        Box2DBoxData box2DBoxData;
        box2DBoxData.bodyType = bodyType;
        box2DBoxData.position = position;
        box2DBoxData.size = size;
        return physicsAPI->createBody(box2DBoxData);
    }

    inline BodyId initializeCircleBody(BodyType bodyType, Vector2 position, float radius) {
        Box2DCircleData box2DBoxData;
        box2DBoxData.bodyType = bodyType;
        box2DBoxData.position = position;
        box2DBoxData.radius = radius;
        return physicsAPI->createBody(box2DBoxData);
    }
};




