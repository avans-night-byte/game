#pragma once


#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "EntityObject.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "BulletComponent.hpp"
#include "WeaponComponent.hpp"
#include "Inventory/InventoryComponent.hpp"
#include "Build/BuildComponent.hpp"
#include "../Object/CollisionHandler.hpp"
#include "Shopkeeper/TradingComponent.hpp"
#include "Wallet/WalletComponent.hpp"

class Game;

class HealthComponent;

class WeaponComponent;

class RenderComponent;

class Input;

class CharacterComponent : public Component, public CollisionHandler {
    enum MovementDirection {
        Left,
        Right,
        Up,
        Down,
        None
    };

private:
    std::map<MovementDirection, bool> _currentMovementDirection {};
    MovementDirection _latestMovementDirection = MovementDirection::None;

    HealthComponent *_healthComponent = nullptr;
    PhysicsComponent *_physicsComponent = nullptr;
    TransformComponent *_transformComponent = nullptr;
    InventoryComponent *_inventoryComponent = nullptr;
    RenderComponent *_renderComponent = nullptr;
    BuildComponent *_buildComponent = nullptr;
    WeaponComponent *_weapon = nullptr;
    TradingComponent *_tradingComponent = nullptr;
    WalletComponent *_walletComponent = nullptr;


    EntityObject *_contactObject {};

    void resetMovement();

public:
    explicit CharacterComponent(EntityId id);

    void getVelocity(Vector2 &velocity) {
        _physicsComponent->getVelocity(velocity);
    }

    void setVelocity(const Vector2 &velocity) {
        _physicsComponent->setVelocity(velocity);
    }

    // Health
    float getHealth() {
        return _healthComponent->getHealth();
    }

    void setHealth(float hp) {
        _healthComponent->setHealth(hp);
    }

    void die() {
        _healthComponent->die();
    }

    void doDamage(float hp) {
        _healthComponent->doDamage(hp);

        if (this->getHealth() <= 0) {
            this->die();
        }
    }

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    [[nodiscard]] std::string name() const override;


public:
    void onCollisionEnter(EntityObject *self, EntityObject *other) override;

    void onCollisionExit(EntityObject *self, EntityObject *other) override;

    void render() override;

    void update(const Input &inputSystem) override;

    void isIdleAnimation(bool isHor, bool isVer);



};
