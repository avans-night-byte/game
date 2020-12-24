#pragma once

#include "../Component.hpp"

class ZombieComponent : public Component{
public:
    explicit ZombieComponent(EntityId id) : Component(id){};
public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;
};