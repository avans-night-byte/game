#pragma once


#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "EntityObject.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "BulletComponent.hpp"
#include "WeaponComponent.hpp"
#include "Inventory/InventoryComponent.hpp"
#include "../Object/CollisionHandler.hpp"

class Game;
class HealthComponent;
class WeaponComponent;
class RenderComponent;
class Input;

class CharacterComponent : public EntityObject, public CollisionHandler {
    enum MovementDirection {
        Left,
        Right,
        Up,
        Down,
        None
    };

private:
    std::map<MovementDirection, bool> _currentMovementDirection;
    MovementDirection _latestMovementDirection = MovementDirection::None;

    std::unique_ptr<HealthComponent> _healthComponent;
    InventoryComponent* _inventoryComponent = nullptr;
    RenderComponent* _renderComponent = nullptr;
    WeaponComponent* _weapon = nullptr;

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
    void onCollisionEnter(const EntityObject *entityObject) override;

    void onCollisionExit(const EntityObject *entityObject) override;

    void render() override;

    void update(const Input &inputSystem) override;

    void isIdleAnimation(bool isHor, bool isVer);
};
