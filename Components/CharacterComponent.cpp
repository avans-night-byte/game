#include "CharacterComponent.h"

void CharacterComponent::update(const Input &inputSystem) {
    // TODO: Need input system that detects also UpKey (currently only down key is supported)
    if(inputSystem.keyMap.action == "UP")
    {
        currentMovementDirection = MovementDirection::Up;
    }
    else if(inputSystem.keyMap.action == "DOWN")
    {
        currentMovementDirection = MovementDirection::Down;
    }
    else if(inputSystem.keyMap.action == "RIGHT")
    {
        currentMovementDirection = MovementDirection::Right;
    }
    else if(inputSystem.keyMap.action == "LEFT")
    {
        currentMovementDirection = MovementDirection::Left;
    }

    update();
}

void CharacterComponent::fixedUpdate(const float &deltaTime) {
    Vector2 velocity;
    getVelocity(velocity);
    switch (currentMovementDirection) {

        case Left:
            velocity.x = -2000;
            break;
        case Right:
            velocity.x = 2000;
            break;
        case Up:
            velocity.y = -2000;
            break;
        case Down:
            velocity.y = 2000;
            break;
        case None:
            velocity = Vector2();
            break;
    }

    setVelocity(velocity * deltaTime);
}
