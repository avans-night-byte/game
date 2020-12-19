#include "CharacterComponent.hpp"

#include "./Rendering/RenderComponent.hpp"
#include "./Rendering/Animation.hpp"
#include "../../Engine/Managers/ResourceManager.hpp"
#include "WeaponComponent.hpp"
#include "Inventory/InventoryComponent.hpp"

#include <memory>

CharacterComponent::CharacterComponent(EntityId id) : Component(id), _pSpriteSheet(nullptr) {
}

std::string CharacterComponent::name() const {
    return "CharacterComponent";
}

CharacterComponent::CharacterComponent(EntityId id, const Vector2 &position)
        : Component(id) {
    Game *game = Game::getInstance();

    this->resetMovement();
    _physicsComponent = std::make_unique<PhysicsComponent>(id,
                                                           BodyType::Dynamic,
                                                           Vector2(position.x, position.y),
                                                           Vector2(20.0f, 20.0f));
    _physicsComponent->setFixedRotation(true);
    _physicsComponent->setVelocity(Vector2());

    _pSpriteSheet = game->getRenderingApi().loadSpriteSheet("../../Resources/Sprites/character.png",
                                                            "spritesheet_char", 96, 104);


    _transform = std::make_unique<TransformComponent>(id);
    _healthComponent = std::make_unique<HealthComponent>();
    _weapon = std::make_unique<WeaponComponent>(id);
    _inventoryComponent = std::make_unique<InventoryComponent>(id);

    /* Rendering for the character */
//    _renderComponent = std::make_unique<RenderComponent>(id, RenderComponent::RenderType::SPRITE_SHEET,
//                                                         "../../Resources/Sprites/character.png",
//                                                         "spritesheet_char", 96, 104);
//    auto *animation = new Animation(*_renderComponent);
//    animation->addAnimation("Walk Right", {{0, 7},
//                                           {1, 7},
//                                           {2, 7},
//                                           {3, 7},
//                                           {4, 7},
//                                           {5, 7},
//                                           {6, 7},
//                                           {7, 7},
//                                           {8, 7},
//                                           {9, 7}});
//    _renderComponent->setAnimation(animation);
//    animation->activateAnimation("Walk Right");


    game->addComponent(id, _transform.get());
    game->addComponent(id, _physicsComponent.get());

    const RTransform &rPosition = _physicsComponent->getRTransform();
    _transform->refLocation(rPosition.X, rPosition.Y);
    _transform->setRotation(rPosition.rotation);

    _pSpriteSheet->selectSprite(0, 0);
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
        _weapon->shoot(*_transform);
    }


    auto &inputApi = Game::getInstance()->getInputAPI();

    int mx, my;
    inputApi.getMousePosition(mx, my);

    auto mouseVector = Vector2(mx, my);
    auto worldPos = _transform->getPosition();
    auto mouseAngle = atan2(mouseVector.y - worldPos.y, mouseVector.x - worldPos.x);

    const RTransform &rPosition = _physicsComponent->getRTransform();
    _transform->setRotation(rPosition.rotation);

    _physicsComponent->setAngle(mouseAngle);
    _inventoryComponent->update(inputSystem);
}

void CharacterComponent::fixedUpdate(const float &deltaTime) {
    Vector2 velocity;
    getVelocity(velocity);

    std::map<MovementDirection, bool>::iterator it;
    bool movingHor = false;
    bool movingVer = false;

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

                velocity.y = 2000;
                movingVer = true;
                break;
            case None:
                break;
        }

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
    Vector2 v2 = _transform->getPosition();
    _pSpriteSheet->drawSelectedSprite(v2.x - 42.5f, v2.y - 75.0f, 1,
                                      _transform->rotation);

    _inventoryComponent->render();
}

void CharacterComponent::startContact(b2Contact *contact) {

}

void CharacterComponent::endContact(b2Contact *contact) {

}

void CharacterComponent::initialize(EntityObject &entityParent) {

}