#pragma once

#include "Component.hpp"
#include "TransformComponent.hpp"
#include "../Object/Pool.hpp"
#include "../Game.hpp"
#include "../Scenes/LevelBase.hpp"
#include <string>

class BulletComponent;

class WeaponComponent : public Component {
public:
    explicit WeaponComponent(EntityId id);

private:
    Pool &_bulletPool;

public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void shoot(const TransformComponent &transform);
};