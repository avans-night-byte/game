#pragma once


#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "Component.hpp"
#include "../Game.hpp"
#include "WorldPositionComponent.hpp"
#include "PhysicsComponent.h"
#include "HealthComponent.hpp"

class CharacterComponent : public Component {
    // TODO: Could make a enum with bitmask flags
    enum MovementDirection
    {
        Left,
        Right,
        Up,
        Down,
        None
    };

private:
    std::map<MovementDirection, bool> currentMovementDirection;
    Spritesheet *spriteSheet;
    unique_ptr<WorldPositionComponent> worldPosition;
    unique_ptr<PhysicsComponent> physicsComponent;
    unique_ptr<HealthComponent> healthComponent;
    void resetMovement();

public:
    explicit CharacterComponent(EntityId id,
                                const EngineRenderingAPI *renderingApi,
                                const Vector2 &position) : Component(id) {
        Game *game = Game::getInstance();

        this->resetMovement();
        physicsComponent = make_unique<PhysicsComponent>(id,
                                                         BodyType::Dynamic,
                                                         Vector2(position.x, position.y),
                                                         Vector2(20, 40));
        physicsComponent->setFixedRotation(true);
        physicsComponent->setVelocity(Vector2());

        healthComponent = make_unique<HealthComponent>();

        spriteSheet = renderingApi->createSpriteSheet("../../Resources/Sprites/character.png",
                                                      "spritesheet_char", 8, 11, 100, 105);

        worldPosition = make_unique<WorldPositionComponent>(id);

        game->addComponent(id, worldPosition.get());
        game->addComponent(id, physicsComponent.get());

        const RPosition &rPosition = physicsComponent->getRPosition();
        worldPosition->setLocation(rPosition.X, rPosition.Y);

        spriteSheet->select_sprite(0, 0);
    }

    // Velocity
    void getVelocity(Vector2 &velocity) {
        physicsComponent->getVelocity(velocity);
    }

    void setVelocity(const Vector2 &velocity) {
        physicsComponent->setVelocity(velocity);
    }

    // Rendering
    void update(const Input &inputSystem);

    void fixedUpdate(const float& deltaTime);

    inline const Spritesheet &getSpriteSheet() {
        return *spriteSheet;
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
        Game::getInstance()->resetGame();
    }

    void doDamage(float hp) {
        healthComponent->doDamage(hp);

        if (this->getHealth() <= 0) {
            this->die();
        }
    }

protected:
    void update() override {
        spriteSheet->draw_selected_sprite(*worldPosition->x - 42.5f, *worldPosition->y - 55.0f);
    }
};
