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
    void update() override {

    }

    void fixedUpdate(const float &deltaTime) override {

    }

    string name() const override {
        return "ExplosionCrate";
    }

    Component *clone(EntityId entityId, const LevelResources::component *component) override {
        return new ExplosionCrate(entityId);
    }

public:
    void startContact() override {

    }

    void endContact() override {

    }
};