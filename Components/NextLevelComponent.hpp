#pragma once


#include <string>
#include "Component.hpp"
#include "../../Engine/Physics/ContactHandler.hpp"

// TODO: Don't use ContactHandler of Engine but of API (which does not exist yet).
class NextLevelComponent : public Component, public ContactHandler {
public:
    std::string NextLevel;
    bool hasContactWithPlayer = false;

    explicit NextLevelComponent(EntityId id) : Component(id) {

    }

    void startContact(b2Contact *contact) override;

    void endContact(b2Contact *contact) override;

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

public:

    [[nodiscard]] std::string name() const override;
};


