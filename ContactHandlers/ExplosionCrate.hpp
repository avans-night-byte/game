#pragma once

#include "../../Engine/Physics/ContactHandler.hpp"
#include "../Components/Component.hpp"

class ExplosionCrate : public Component, public ContactHandler {
public:
    ExplosionCrate(EntityId id) : Component(id)
    {

    }

    ~ExplosionCrate() {

    }

public:
    void render() override {

    }

    void update(const Input &inputSystem) override {

    }

    void fixedUpdate(const float &deltaTime) override {

    }

    std::string name() const override {
        return "ExplosionCrate";
    }

    Component *clone(EntityId entityId, const Components::component *component) override {
        return new ExplosionCrate(entityId);
    }

    void initialize(EntityObject &entityParent) override {

    }

public:
    void startContact(b2Contact *contact) override {
    }

    void endContact(b2Contact *contact) override {

    }
};