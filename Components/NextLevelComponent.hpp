#pragma once


#include <string>
#include "Component.hpp"
#include "../Object/CollisionHandler.hpp"
#include "PlayerSpawnerComponent.hpp"

// TODO: Don't use ContactHandler of Engine but of API (which does not exist yet).
class NextLevelComponent : public Component, public CollisionHandler {
public:
    std::string NextLevel;
    bool hasContactWithPlayer = false;

    std::string nextLevelSpawnPointName{};

    explicit NextLevelComponent(EntityId id) : Component(id) {

    }

    void onCollisionEnter(EntityObject *self, EntityObject *other) override;

    void onCollisionExit(EntityObject *self, EntityObject *other) override;

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void postInitialize(EntityObject &entityObject) override;

public:

    [[nodiscard]] std::string name() const override;
};


