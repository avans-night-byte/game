#pragma once


#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "BulletComponent.hpp"
#include "WeaponComponent.hpp"
#include "../Game.hpp"

class Game;
class HealthComponent;
class WeaponComponent;
class Input;

class CharacterComponent : public Component, public ContactHandler {
    enum MovementDirection {
        Left,
        Right,
        Up,
        Down,
        None
    };

private:
    std::map<MovementDirection, bool> _currentMovementDirection;
    Spritesheet *_pSpriteSheet{};

    unique_ptr<TransformComponent> _transform;
    unique_ptr<HealthComponent> _healthComponent;
    unique_ptr<PhysicsComponent> _physicsComponent;

    unique_ptr<WeaponComponent> _weapon;

    void resetMovement();

public:
    explicit CharacterComponent(EntityId id);

    CharacterComponent(EntityId id, const Vector2 &position);

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

    inline const Spritesheet &getSpriteSheet() {
        return *_pSpriteSheet;
    }

    [[nodiscard]] Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void initializeWeapons(std::vector<std::unique_ptr<EntityObject>>& entities);

    [[nodiscard]] std::string name() const override;


public:
    void startContact(b2Contact *contact) override;

    void endContact(b2Contact *contact) override;

    void render() override;

    void update(const Input &inputSystem) override;
};