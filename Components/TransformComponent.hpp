#pragma once

#include "Component.hpp"
#include <string>


#include "../../Engine/Helpers/Vector2.hpp"
#include "EntityObject.hpp"
#include <math.h>

namespace Components {
    class component;
}

class TransformComponent : public Component {
private:
    float _x;
    float _y;

    const float *_physicsX = nullptr;
    const float *_physicsY = nullptr;

public:
    float rotation = 0;



public:
    void render() override;

    void update(const Input &inputSystem) override;

    void refLocation(const float &rX, const float &rY);

    void setRotation(float r);

    explicit TransformComponent(EntityId id) : Component(id) {}

    void fixedUpdate(const float &deltaTime) override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

public:
    [[nodiscard]] Vector2 right() const {
        return Vector2(cos(rotation / 180.f * M_PI), sin(rotation / 180.f * M_PI));
    }

    [[nodiscard]] Vector2 left() const {
        return right() * -1.f;
    }

    [[nodiscard]] Vector2 up() const {
        return Vector2(sin(rotation / 180.f * M_PI), -cos(rotation / 180.f * M_PI));
    }

    [[nodiscard]] Vector2 down() const {
        return up() * -1.0f;
    }

public:

    [[nodiscard]] Vector2 getPosition() const {
        if(_physicsX == nullptr || _physicsY == nullptr){
            return Vector2( _x, _y);
        }
        return Vector2(*_physicsX + _x, *_physicsY + _y);
    }

    [[nodiscard]]std::string name() const override;

    TransformComponent &operator=(Vector2& v2);

};