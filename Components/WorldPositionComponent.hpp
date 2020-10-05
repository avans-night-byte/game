//
// Created by sasch on 05/10/2020.
//

#ifndef NIGHTBYTE_WORLDPOSITIONCOMPONENT_HPP
#define NIGHTBYTE_WORLDPOSITIONCOMPONENT_HPP


#include "Component.hpp"

class WorldPositionComponent : public Component {
public:
    int x, y = 0;
public:
    void update() override;
    void SetLocation(int x, int y);
    WorldPositionComponent(EntityId id) : Component(id) {}
};

#endif //NIGHTBYTE_WORLDPOSITIONCOMPONENT_HPP
