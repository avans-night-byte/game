#include "ZombieComponent.hpp"

#include "../Rendering/Animation.hpp"
#include "../Rendering/RenderComponent.hpp"
#include "../Wallet/WalletComponent.hpp"
#include "../../Game.hpp"
#include "../../Helpers/GameTime.h"

#include <string>

void ZombieComponent::render() {

}

void ZombieComponent::update(const Input &inputSystem) {

    float current = GameTime::getInstance().getTime();
    if(current - _timeSinceLastSound >= 100){
        _timeSinceLastSound = current;
        auto soundIndex = rand() % 3 + 1;

        Game::getInstance()->getAudioAPI().playFromMemory("zombie_roar" + std::to_string(soundIndex));
    }

}

void ZombieComponent::fixedUpdate(const float &deltaTime) {

}

std::string ZombieComponent::name() const {
    return "ZombieComponent";
}

Component *ZombieComponent::build(EntityId entityId, const Components::component *component) {
    return new ZombieComponent(entityId);
}

void ZombieComponent::initialize(EntityObject &entityParent) {
    auto *renderComponent = entityParent.getComponent<RenderComponent>();
    auto *physicsComponent = entityParent.getComponent<PhysicsComponent>();
    physicsComponent->setFixedRotation(true);
    physicsComponent->collisionHandlers.push_back(this);

    _timeSinceLastSound = GameTime::getInstance().getTime();

    auto *animation = new Animation(*renderComponent);
    animation->addAnimation("Walk", {{0, 0},
                                     {1, 0},
                                     {2, 0}});

    animation->speed = 100;

    renderComponent->setAnimation(animation);
    animation->activateAnimation("Walk");
}

// TODO: Make Component "Hittable".
void ZombieComponent::onCollisionEnter(EntityObject *self, EntityObject *other) {
    if (other == nullptr)
        return;

    auto *bullet = other->getComponent<BulletComponent>();
    if (bullet) {
        bool hasHit = bullet->hasHit;
        Game::getInstance()->addEventBodyHandler(
                [self, other, bullet, hasHit] {
                    if (!hasHit) {
                        self->destroy();
                        auto wallet = Game::getInstance()->getCharacter()->getComponent<WalletComponent>();
                        wallet->addZombytes(10);
                        wallet->addScore(100);

                        auto soundIndex = rand() % 2 + 1;
                        Game::getInstance()->getAudioAPI().playFromMemory("zombie_die" + std::to_string(soundIndex));
                    }
                    bullet->hasHit = false;
                }
        );
        bullet->hasHit = true;
    }
}

void ZombieComponent::onCollisionExit(EntityObject *self, EntityObject *other) {

}

void ZombieComponent::postInitialize(EntityObject &entityObject) {

}
