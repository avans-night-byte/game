#pragma once


#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"
#include "HealthComponent.hpp"
#include "../Game.hpp"

class Game;
class HealthComponent;
class Input;

class CharacterComponent : public Component, public ContactHandler {
    // TODO: Could make a enum with bitmask flags
    enum MovementDirection {
        Left,
        Right,
        Up,
        Down,
        None
    };

private:
    std::map<MovementDirection, bool> currentMovementDirection;
    Spritesheet *spriteSheet{};
    unique_ptr<TransformComponent> worldPosition;
    unique_ptr<HealthComponent> healthComponent;
    unique_ptr<PhysicsComponent> physicsComponent;

    void resetMovement();

public:
    explicit CharacterComponent(EntityId id);

    CharacterComponent(EntityId id, const Vector2 &position);

    void getVelocity(Vector2 &velocity) {
        physicsComponent->getVelocity(velocity);
    }

    void setVelocity(const Vector2 &velocity) {
        physicsComponent->setVelocity(velocity);
    }

    // Health
    float getHealth() {
        return healthComponent->getHealth();
    }

    void setHealth(float hp) {
        healthComponent->setHealth(hp);
    }

    void die() {
        healthComponent->die();
    }

    void doDamage(float hp) {
        healthComponent->doDamage(hp);

        if (this->getHealth() <= 0) {
            this->die();
        }
    }

    void fixedUpdate(const float &deltaTime) override;

    inline const Spritesheet &getSpriteSheet() {
        return *spriteSheet;
    }

    [[nodiscard]] Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    [[nodiscard]] std::string name() const override;


public:
    void startContact(b2Contact *contact) override;

    void endContact(b2Contact *contact) override;

    void render() override;

    void update(const Input &inputSystem) override;
};
