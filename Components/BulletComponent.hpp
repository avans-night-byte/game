#pragma once

#include "Component.hpp"

class PhysicsComponent;
class TransformComponent;

class BulletComponent : public Component {
public:
    explicit BulletComponent(EntityId id) : Component(id){

    }

public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;
};