#pragma once

#include "Component.hpp"
#include <string>


#include "../../Engine/Vector2.hpp"

namespace Components {
    class component;
}

class TransformComponent : public Component {
public:
    float rotation = 0;
    const float *physicsX = nullptr;
    const float *physicsY = nullptr;

public:
    void render() override;

    void update(const Input &inputSystem) override;

    void refLocation(const float &rX, const float &rY);

    void setRotation(float r);

    explicit TransformComponent(EntityId id) : Component(id) {}

    void fixedUpdate(const float &deltaTime) override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    [[nodiscard]] Vector2 getPosition() const { return Vector2(*physicsX, *physicsY); }

    [[nodiscard]]std::string name() const override;
};