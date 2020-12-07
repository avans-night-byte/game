#pragma once

#include "Component.hpp"
#include <string>

class WorldPositionComponent : public Component {
public:
    const float *x = 0;
    const float *y = 0;
public:
    void update() override;

    void setLocation(const float &rX, const float &rY);

    explicit WorldPositionComponent(EntityId id) : Component(id) {}

    void fixedUpdate(const float &deltaTime) override;

    Component *Clone(EntityId entityId, const LevelResources::component *component) override;

    [[nodiscard]] std::string name() const override;
};