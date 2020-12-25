#include "CharacterComponent.hpp"
#include "../NextLevelComponent.hpp"
#include "../Shopkeeper/ShopkeeperComponent.hpp"
#include "ZombieComponent.hpp"


#include <memory>

std::string CharacterComponent::name() const {
    return "CharacterComponent";
}

CharacterComponent::CharacterComponent(EntityId id) : Component(id) {
    this->resetMovement();
}

void CharacterComponent::update(const Input &inputSystem) {
    bool stopped = false;

    if (inputSystem.keyMap.type == KeyType::KeyUp) {
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

    if (_contactObject && inputSystem.keyMap.action == "INTERACT") {

        auto shopKeeper = _contactObject->getComponent<ShopkeeperComponent>();

        if (shopKeeper) {
            TransactionData data(_walletComponent->getExperience(), _walletComponent->getZombytes(),
                                 _walletComponent->getScore());

            data.setTransactionCallback(
                    std::bind(&CharacterComponent::transactionCallback, this, std::placeholders::_1));

            shopKeeper->startTransaction(data);
            _isShopping = shopKeeper->startedTransaction();

        } else if (_contactObject->getType() != EntityObject::EntityType::level_change &&
                   _contactObject->getType() != EntityObject::EntityType::character) {

            _buildComponent->pickUpObject(*_contactObject);
            _contactObject->destroy();
            _contactObject = nullptr;
        }
    }

    if (inputSystem.keyMap.action == "INVENTORY") {
        _inventoryComponent->showInventory();
    }

    if (inputSystem.keyMap.action == "CLICK_LEFT") {

        if (_isShopping) return;

        if (_inventoryComponent->isInventoryOpen()) {
            _inventoryComponent->hideInventory();
            _inventoryComponent->click(inputSystem);
            return;
        }

        _weapon->shoot(*_transformComponent);
    }
    if (inputSystem.keyMap.action == "CLICK_RIGHT" && !_inventoryComponent->isInventoryOpen()) {
        _buildComponent->placeObject(*_transformComponent);
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
}

void CharacterComponent::transactionCallback(TransactionData &data) {
    _walletComponent->addItemsFromTransaction(data);

    for (auto &item : data.getInventoryItems()) {
        _inventoryComponent->addToInventory(item);
    }
    _isShopping = false;
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

        moveCharacter(velocity * deltaTime);
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
}

void CharacterComponent::onCollisionEnter(EntityObject *self, EntityObject *other) {
    if (other != nullptr) {
        _contactObject = other;

        if (auto zombie = other->getComponent<ZombieComponent>()) {
            _healthComponent->doDamage(10);
        }
    }
}

void CharacterComponent::onCollisionExit(EntityObject *self, EntityObject *other) {
    if (_contactObject == other)
        _contactObject = nullptr;
}


void CharacterComponent::initialize(EntityObject &entityParent) {
    _renderComponent = entityParent.getComponent<RenderComponent>();
    _weapon = entityParent.getComponent<WeaponComponent>();

    _physicsComponent = entityParent.getComponent<PhysicsComponent>();
    _physicsComponent->collisionHandlers.push_back(this);

    _transformComponent = entityParent.getComponent<TransformComponent>();

    _healthComponent = entityParent.getComponent<HealthComponent>();

    _inventoryComponent = entityParent.getComponent<InventoryComponent>();
    _walletComponent = entityParent.getComponent<WalletComponent>();
    _walletComponent->addZombytes(999999);

    _buildComponent = entityParent.getComponent<BuildComponent>();

    _inventoryComponent->getOnInventoryClickEventManager() += std::bind(&BuildComponent::setBuildObject,
                                                                        _buildComponent, std::placeholders::_1);
    _buildComponent->getPickupEventHandler() += std::bind(&InventoryComponent::addEntityToInventory,
                                                          _inventoryComponent, std::placeholders::_1);

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

    animation->speed = 10;

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

