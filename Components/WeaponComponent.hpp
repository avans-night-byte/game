#pragma once

#include "Component.hpp"
#include "TransformComponent.hpp"
#include <string>

class BulletComponent;

class WeaponComponent : public Component {
public:
    WeaponComponent(EntityId id, EntityObject &bullet) : Component(id), _bulletEntity(bullet) {

    }

private:
    EntityObject& _bulletEntity; // TODO: Object system for bullets.

public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void shoot(const TransformComponent &transform);
};