#pragma once


#include <string>
#include "Component.hpp"
#include "../../Engine/Physics/ContactHandler.hpp"

// TODO: Don't use ContactHandler of Engine but of API (which does not exist yet).
class NextLevelComponent : public Component, public ContactHandler {
public:
    std::string NextLevel = "Wow look at me!";

    explicit NextLevelComponent(EntityId id) : Component(id) {

    }

    void startContact() override;

    void endContact() override;

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] Component *clone(EntityId entityId, const Components::component *component) override;

    std::string name() const override;
};


