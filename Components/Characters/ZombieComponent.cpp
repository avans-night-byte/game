#include "ZombieComponent.hpp"

#include "../Rendering/Animation.hpp"
#include "../Rendering/RenderComponent.hpp"
#include "../EntityObject.hpp"

#include <string>

void ZombieComponent::render() {

}

void ZombieComponent::update(const Input &inputSystem) {

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
    entityParent.getComponent<PhysicsComponent>()->setFixedRotation(true);

    auto *animation = new Animation(*renderComponent);
    animation->addAnimation("Walk", {{0, 0}, {1, 0}, {2, 0}});

    animation->speed = 100;

    renderComponent->setAnimation(animation);
    animation->activateAnimation("Walk");
}
