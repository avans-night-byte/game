#pragma once


#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "Component.hpp"
#include "WorldPositionComponent.hpp"
#include "PhysicsComponent.hpp"

class Game;
class Input;

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
    void resetMovement();

public:
    CharacterComponent(EntityId id,
                                const EngineRenderingAPI *renderingApi,
                                const Vector2 &position);

    void getVelocity(Vector2 &velocity) {
        physicsComponent->getVelocity(velocity);
    }

    void setVelocity(const Vector2 &velocity) {
        physicsComponent->setVelocity(velocity);
    }

    void update(const Input &inputSystem);

    void fixedUpdate(const float& deltaTime);

    inline const Spritesheet &getSpriteSheet() {
        return *spriteSheet;
    }

    unique_ptr<Component> Clone(EntityId entityId) override;

protected:
    void update() override {
        spriteSheet->draw_selected_sprite(*worldPosition->x - 42.5f, *worldPosition->y - 75.0f);
    }
};
