#pragma once

#include "Component.hpp"

class WorldPositionComponent : public Component {
public:
    int x = 0, y = 0;
public:
    void update() override;

    void setLocation(int x, int y);

    WorldPositionComponent(EntityId id) : Component(id) {}
};