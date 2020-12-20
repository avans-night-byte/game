#include "CharacterComponent.hpp"

#include "NextLevelComponent.hpp"

#include <memory>

std::string CharacterComponent::name() const {
    return "CharacterComponent";
}

CharacterComponent::CharacterComponent(EntityId id) : EntityObject(id) {
    this->resetMovement();
    _healthComponent = std::make_unique<HealthComponent>();
}

void CharacterComponent::update(const Input &inputSystem) {
    bool stopped = false;

    if (inputSystem.keyMap.type == SDL_KEYUP) {
        stopped = true;
    }

    if (inputSystem.keyMap.action == "UP") {
        _currentMovementDirection[MovementDirection::Up] = !stopped;
    }
    if (inputSystem.keyMap.action == "DOWN") {
        _currentMovementDirection[MovementDirection::Down] = !stopped;
    }
    if (inputSystem.keyMap.action == "RIGHT") {
        _currentMovementDirection[MovementDirection::Right] = !stopped;
    }
    if (inputSystem.keyMap.action == "LEFT") {
        _currentMovementDirection[MovementDirection::Left] = !stopped;
    }

    if (inputSystem.keyMap.action == "ESCAPE") {
        auto &p = *ResourceManager::getInstance();
        p.loadResource("Options");
    }

    if (inputSystem.keyMap.action == "CLICK_LEFT" && !_inventoryComponent->isMenuOpen()) {
        _weapon->shoot(*_transformComponent);
    }


    auto &inputApi = Game::getInstance()->getInputAPI();

    int mx, my;
    inputApi.getMousePosition(mx, my);

    auto mouseVector = Vector2(mx, my);
    auto worldPos = _transformComponent->getPosition();
    auto mouseAngle = atan2(mouseVector.y - worldPos.y, mouseVector.x - worldPos.x);

    const RTransform &rPosition = _physicsComponent->getRTransform();
    _transformComponent->setRotation(rPosition.rotation);

    _physicsComponent->setAngle(mouseAngle);
    _inventoryComponent->update(inputSystem);
}

void CharacterComponent::fixedUpdate(const float &deltaTime) {
    Vector2 velocity;
    getVelocity(velocity);

    std::map<MovementDirection, bool>::iterator it;
    bool movingHor = false;
    bool movingVer = false;

    Animation &animation = *_renderComponent->getAnimation();

    for (it = _currentMovementDirection.begin(); it != _currentMovementDirection.end(); it++) {
        switch (it->first) {
            case Left:
                if (!it->second && !movingHor) {
                    velocity.x = 0;
                    movingHor = false;
                    break;
                }

                if (movingHor)
                    break;

                animation.activateAnimation("Walk Left");
                _latestMovementDirection = MovementDirection::Left;
                velocity.x = -2000;
                movingHor = true;
                break;
            case Right:
                if (!it->second && !movingHor) {
                    velocity.x = 0;
                    movingHor = false;
                    break;
                }
                if (movingHor)
                    break;

                animation.activateAnimation("Walk Right");
                _latestMovementDirection = MovementDirection::Right;
                velocity.x = 2000;
                movingHor = true;
                break;
            case Up:
                if (!it->second && !movingVer) {
                    velocity.y = 0;
                    movingVer = false;
                    break;
                }
                if (movingVer)
                    break;

                animation.activateAnimation("Walk Up");
                _latestMovementDirection = MovementDirection::Up;
                velocity.y = -2000;
                movingVer = true;
                break;
            case Down:
                if (!it->second && !movingVer) {
                    velocity.y = 0;
                    movingVer = false;
                    break;
                }
                if (movingVer)
                    break;

                animation.activateAnimation("Walk Down");
                _latestMovementDirection = MovementDirection::Down;
                velocity.y = 2000;
                movingVer = true;
                break;
            case None:
                break;
        }

        this->isIdleAnimation(movingHor, movingVer);

        setVelocity(velocity * deltaTime);

    }
}

void CharacterComponent::resetMovement() {
    _currentMovementDirection[Left] = false;
    _currentMovementDirection[Right] = false;
    _currentMovementDirection[Up] = false;
    _currentMovementDirection[Down] = false;
}

Component *CharacterComponent::build(EntityId entityId, const Components::component *component) {
    return new CharacterComponent(entityId);
}


void CharacterComponent::render() {
    _renderComponent->render();
    _inventoryComponent->render();
}

void CharacterComponent::onCollisionEnter(const EntityObject *entityObject) {
//    if (auto *characterComponent = (NextLevelComponent*)contact->GetFixtureB()->GetBody()->GetUserData().pointer) {
//        std::cout << "contact with nextlevel" << std::endl;
//    }
}

void CharacterComponent::onCollisionExit(const EntityObject *entityObject) {

}


void CharacterComponent::initialize(EntityObject &entityParent) {
    _renderComponent = getComponent<RenderComponent>();
    _inventoryComponent = getComponent<InventoryComponent>();
    _physicsComponent = getComponent<PhysicsComponent>();
    _physicsComponent->collisionHandlers.push_back(this);
    _transformComponent = getComponent<TransformComponent>();

    auto *animation = new Animation(*_renderComponent);
    animation->addAnimation("Walk Right", {{0, 7},
                                           {1, 7},
                                           {2, 7},
                                           {3, 7},
                                           {4, 7},
                                           {5, 7},
                                           {6, 7},
                                           {7, 7},
                                           {8, 7},
                                           {9, 7}});

    animation->addAnimation("Walk Right Idle", {{0, 3}});

    animation->addAnimation("Walk Up", {{0, 6},
                                        {1, 6},
                                        {2, 6},
                                        {3, 6},
                                        {4, 6},
                                        {5, 6},
                                        {6, 6},
                                        {7, 6},
                                        {8, 6},
                                        {9, 6}});

    animation->addAnimation("Walk Up Idle", {{0, 2}});


    animation->addAnimation("Walk Left", {{0, 5},
                                          {1, 5},
                                          {2, 5},
                                          {3, 5},
                                          {4, 5},
                                          {5, 5},
                                          {6, 5},
                                          {7, 5},
                                          {8, 5},
                                          {9, 5}});

    animation->addAnimation("Walk Left Idle", {{0, 1}});

    animation->addAnimation("Walk Down", {{0, 4},
                                          {1, 4},
                                          {2, 4},
                                          {3, 4},
                                          {4, 4},
                                          {5, 4},
                                          {6, 4},
                                          {7, 4},
                                          {8, 4},
                                          {9, 4}});

    animation->addAnimation("Walk Down Idle", {{0, 0}});

    animation->speed = 1;

    _renderComponent->setAnimation(animation);

    const RTransform &rPosition = _physicsComponent->getRTransform();
    _transformComponent->refLocation(rPosition.X, rPosition.Y);
    _transformComponent->setRotation(rPosition.rotation);
}

void CharacterComponent::isIdleAnimation(bool isHor, bool isVer) {
    Animation &animation = *_renderComponent->getAnimation();
    if (!isHor && !isVer) {
        switch (_latestMovementDirection) {
            case Left:
                animation.activateAnimation("Walk Left Idle");
                break;
            case Right:
                animation.activateAnimation("Walk Right Idle");
                break;
            case Up:
                animation.activateAnimation("Walk Up Idle");
                break;
            case Down:
            case None:
                animation.activateAnimation("Walk Down Idle");
                break;
        }
    }
}

