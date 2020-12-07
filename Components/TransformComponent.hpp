#pragma once

#include "Component.hpp"

class TransformComponent : public Component {
public:
    const float *x = 0;
    const float *y = 0;
    float rotation = 0;
public:
    void update() override;

    void setLocation(const float &x, const float &y);
    void setRotation(float rotation);

    TransformComponent(EntityId id) : Component(id) {}
};