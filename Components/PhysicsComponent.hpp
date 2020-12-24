#pragma once

#include "../../API/Physics/EnginePhysicsAPI.hpp"
#include "../../API/RTransform.hpp"
#include "Component.hpp"
#include "../Object/CollisionHandler.hpp"

namespace Components {
    class physicsComponent;
}
class TransformComponent;
class EntityObject;




class PhysicsComponent : public Component, public ContactHandler {
private:
    const PhysicsAPI &_physicsAPI;
    unsigned int _bodyId = 0;
    EntityObject *_parent = nullptr;

    std::string contactHandlerName {};
public:
    inline const std::string& getContactHandlerName() {
        return contactHandlerName;
    }

    void destroyBody();

public:
    std::vector<CollisionHandler*> collisionHandlers{};

    explicit PhysicsComponent(EntityId id);

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size);

    PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius);

    ~PhysicsComponent() override = default;

    inline RTransform getRTransform() {
        return _physicsAPI.getRPosition(_bodyId);
    }

    inline void getVelocity(Vector2 &velocity) {
        _physicsAPI.GetVelocity(velocity, _bodyId);
    }

    inline void setVelocity(const Vector2 &velocity) {
        _physicsAPI.setLinearVelocity(_bodyId, velocity);
    }

    inline void setFixedRotation(bool value) {
        _physicsAPI.setFixedRotation(_bodyId, value);
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

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void fixedUpdate(const float &deltaTime) override;

    void render() override;

    void update(const Input &inputSystem) override;

    void startContact(b2Contact *contact, bool isA) override;

    void endContact(b2Contact *contact, bool isA) override;

    void setAngle(float angle);

private:
    inline BodyId initializeBoxBody(BodyType bodyType, Vector2 position, Vector2 size) {
        Box2DBoxData box2DBoxData;
        box2DBoxData.bodyType = bodyType;
        box2DBoxData.position = position;
        box2DBoxData.contactHandler = this;
        box2DBoxData.size = size;
        return _physicsAPI.createBody(box2DBoxData);
    }

    inline BodyId initializeCircleBody(BodyType bodyType, Vector2 position, float radius) {
        Box2DCircleData box2DCircleData;
        box2DCircleData.bodyType = bodyType;
        box2DCircleData.position = position;
        box2DCircleData.radius = radius;
        box2DCircleData.contactHandler = this;
        return _physicsAPI.createBody(box2DCircleData);
    }

public:
    static TransformComponent *setPositionPhysicsResource(EntityObject *pObject, Components::physicsComponent &component);

    void setTransform(Vector2 pos, float angle);

    void addForce(const Vector2 &position, Vector2 force);

    void setEnabled(bool b);

    EntityObject* getParent() {
        return _parent;
    }

    void addFixture(Components::component *pComponent);
};




