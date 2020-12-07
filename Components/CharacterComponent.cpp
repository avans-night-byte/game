#include "CharacterComponent.h"



void CharacterComponent::update(const Input &inputSystem) {
    bool stopped = false;

    if(inputSystem.keyMap.type == SDL_KEYUP){
        stopped = true;
    }

    if(inputSystem.keyMap.action == "UP")
    {
        currentMovementDirection[MovementDirection::Up] = !stopped;
    }
    if(inputSystem.keyMap.action == "DOWN")
    {
        currentMovementDirection[MovementDirection::Down] = !stopped;
    }
    if(inputSystem.keyMap.action == "RIGHT")
    {
        currentMovementDirection[MovementDirection::Right] = !stopped;
    }
    if(inputSystem.keyMap.action == "LEFT")
    {
        currentMovementDirection[MovementDirection::Left] = !stopped;
    }





    auto inputApi = Game::getInstance()->getInputAPI();

    int mx, my;
    inputApi->getMousePosition(mx,my);

    auto mouseVector = Vector2(mx, my);
    auto worldPos = Vector2(*worldPosition->x, *worldPosition->y);
    auto mouseAngle = atan2(mouseVector.y - worldPos.y, mouseVector.x - worldPos.x);

    physicsComponent->setAngle(mouseAngle);
    _renderingApi->drawLine(mouseVector, worldPos);

    update();
}

void CharacterComponent::fixedUpdate(const float &deltaTime) {
    Vector2 velocity;
    getVelocity(velocity);

    map<MovementDirection, bool>::iterator it;
    bool movingHor = false;
    bool movingVer = false;

    for ( it = currentMovementDirection.begin(); it != currentMovementDirection.end(); it++ )
    {
        switch (it->first) {
            case Left:
                if(!it->second && movingHor != true){
                    velocity.x = 0;
                    movingHor = false;
                    break;
                }

                if(movingHor)
                    break;

                velocity.x = -2000;
                movingHor = true;
                break;
            case Right:
                if(!it->second && !movingHor){
                    velocity.x = 0;
                    movingHor = false;
                    break;
                }
                if(movingHor)
                    break;

                velocity.x = 2000;
                movingHor = true;
                break;
            case Up:
                if(!it->second && !movingVer){
                    velocity.y = 0;
                    movingVer = false;
                    break;
                }
                if(movingVer)
                    break;

                velocity.y = -2000;
                movingVer = true;
                break;
            case Down:
                if(!it->second && !movingVer){
                    velocity.y = 0;
                    movingVer = false;
                    break;
                }
                if(movingVer)
                    break;

                velocity.y = 2000;
                movingVer = true;
                break;
        }

        setVelocity(velocity * deltaTime);

    }
}

void CharacterComponent::resetMovement() {
    currentMovementDirection[Left]  = false;
    currentMovementDirection[Right] = false;
    currentMovementDirection[Up]    = false;
    currentMovementDirection[Down]  = false;
}
