#include <Generated/level-resources.hxx>
#include "../Game.hpp"
#include "../../API/RPosition.hpp"


#include "PhysicsComponent.hpp"


void PhysicsComponent::fixedUpdate(const float &deltaTime) {

}

PhysicsComponent::PhysicsComponent(EntityId id)
        : Component(id), physicsAPI(Game::getInstance()->getPhysicsAPI()) {

}

PhysicsComponent::PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size)
        : Component(id),
          physicsAPI(Game::getInstance()->getPhysicsAPI()),
          bodyId{this->initializeBoxBody(bodyType, position, size)} {


}

PhysicsComponent::PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius)
        : Component(id),
          physicsAPI(Game::getInstance()->getPhysicsAPI()),
          bodyId(this->initializeCircleBody(bodyType, position, radius)) {


}

string PhysicsComponent::name() const {
    return "PhysicsComponent";
}

Component *PhysicsComponent::clone(EntityId entityId,
                                   const Components::component *component) {

    auto newPhysicsComponent = new PhysicsComponent(entityId);
    auto &physicsComponent = component->physicsComponent().get();
    auto bodyTypeString = std::string(physicsComponent.bodyType().c_str());

    auto &shapeCircle = physicsComponent.bodyShape().circle();
    auto &shapeBox = physicsComponent.bodyShape().box();


    BodyType bodyType = StringToBodyType(bodyTypeString);
    Vector2 position = Vector2(physicsComponent.position().x(), physicsComponent.position().y());

    /* Shape */
    if (shapeCircle != nullptr) {
        Box2DCircleData circleData{};
        circleData.radius = shapeCircle->radius();
        circleData.position = position;
        circleData.bodyType = bodyType;
        circleData.isSensor = physicsComponent.isSensor();
        circleData.userData = newPhysicsComponent;

        newPhysicsComponent->bodyId = physicsAPI->createBody(circleData);
    } else {
        // BOX
        Box2DBoxData boxData{};
        boxData.size = Vector2(shapeBox->width(), shapeBox->height());
        boxData.position = position;
        boxData.bodyType = bodyType;
        boxData.isSensor = physicsComponent.isSensor();
        boxData.userData = newPhysicsComponent;

        newPhysicsComponent->bodyId = physicsAPI->createBody(boxData);
    }

    return newPhysicsComponent;
}

void PhysicsComponent::startContact() {
    for (auto &contactHandler : contactHandlers) {
        contactHandler->startContact();
    }
}

void PhysicsComponent::endContact() {
    for (auto &contactHandler : contactHandlers) {
        contactHandler->endContact();
    }
}

void PhysicsComponent::render() {

}

void PhysicsComponent::update(const Input &inputSystem) {

}

void PhysicsComponent::setAngle(float angle) {
    physicsAPI->setAngle(bodyId, angle );
}
