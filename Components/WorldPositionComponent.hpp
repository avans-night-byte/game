#pragma once

#include "Component.hpp"

class WorldPositionComponent : public Component {
public:
    const float *x = 0;
    const float *y = 0;
public:
    void update() override;

    void setLocation(const float &x, const float &y);

    WorldPositionComponent(EntityId id) : Component(id) {}
};