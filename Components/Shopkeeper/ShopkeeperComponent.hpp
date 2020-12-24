#pragma once

#include <string>

#include "../Component.hpp"
#include "../EntityObject.hpp"
#include "../Inventory/InventoryComponent.hpp"
#include "../Rendering/RenderComponent.hpp"
#include "TradingComponent.hpp"


class ShopkeeperComponent : public Component, public CollisionHandler {
private:
    PhysicsComponent *_physicsComponent = nullptr;
    TransformComponent *_transformComponent = nullptr;
    InventoryComponent *_inventoryComponent = nullptr;
    RenderComponent *_renderComponent = nullptr;
    TradingComponent *_tradingComponent = nullptr;

    bool _startedTransaction = false;

public:
    void startTransaction();

#pragma region Component
public:

    ~ShopkeeperComponent() override;

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;
#pragma endregion Component

#pragma region CollisionHandler
public:
    void onCollisionEnter(EntityObject *self, EntityObject *other) override;

    void onCollisionExit(EntityObject *self, EntityObject *other) override;

#pragma endregion CollisionHandler
};


