#pragma once

#include "Component.hpp"
#include "../Object/CollisionHandler.hpp"

class PhysicsComponent;
class TransformComponent;

class BulletComponent : public Component, CollisionHandler {
public:
    bool hasHit = false;

    explicit BulletComponent(EntityId id) : Component(id){

    }

public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void postInitialize(EntityObject &entityObject) override;

private:
    void onCollisionEnter(EntityObject *self, EntityObject *other) override;

    void onCollisionExit(EntityObject *self, EntityObject *other) override;
};