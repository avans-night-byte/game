#include <Generated/level-resources.hxx>
#include <Generated/components.hxx>
#include "../Game.hpp"

#include "PhysicsComponent.hpp"
#include "EntityObject.hpp"
#include "TransformComponent.hpp"


void PhysicsComponent::fixedUpdate(const float &deltaTime) {

}

PhysicsComponent::PhysicsComponent(EntityId id)
        : Component(id), _physicsAPI(Game::getInstance()->getPhysicsAPI()) {

}

PhysicsComponent::PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size)
        : Component(id),
          _physicsAPI(Game::getInstance()->getPhysicsAPI()),
          _bodyId{this->initializeBoxBody(bodyType, position, size)} {


}

PhysicsComponent::PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius)
        : Component(id),
          _physicsAPI(Game::getInstance()->getPhysicsAPI()),
          _bodyId(this->initializeCircleBody(bodyType, position, radius)) {
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
        circleData.isSensor = physicsComponent.isSensor().present() && physicsComponent.isSensor().get();
        circleData.isBullet = physicsComponent.isBullet().present() && physicsComponent.isBullet().get();
        circleData.userData = newPhysicsComponent;

        newPhysicsComponent->_bodyId = _physicsAPI.createBody(circleData);
    } else {
        // BOX
        Box2DBoxData boxData{};
        boxData.size = Vector2(shapeBox->width(), shapeBox->height());
        boxData.position = position;
        boxData.bodyType = bodyType;
        boxData.isSensor = physicsComponent.isSensor().present() && physicsComponent.isSensor().get();
        boxData.isBullet = physicsComponent.isBullet().present() && physicsComponent.isBullet().get();
        boxData.userData = newPhysicsComponent;

        newPhysicsComponent->_bodyId = _physicsAPI.createBody(boxData);
    }

    return newPhysicsComponent;
}

void PhysicsComponent::startContact(b2Contact *contact) {
    for (auto &contactHandler : contactHandlers) {
        contactHandler->startContact(contact);
    }
}

void PhysicsComponent::endContact(b2Contact *contact) {
    for (auto &contactHandler : contactHandlers) {
        contactHandler->endContact(contact);
    }
}

void PhysicsComponent::render() {

}

void PhysicsComponent::update(const Input &inputSystem) {

}

void PhysicsComponent::setAngle(float angle) {
    _physicsAPI.setAngle(_bodyId, angle );
}

void PhysicsComponent::destroyBody() {
    _physicsAPI.destroyBody(_bodyId);
}

TransformComponent *PhysicsComponent::setPositionPhysicsResource(EntityObject *pObject, Components::physicsComponent &component) {
    for (auto &c : pObject->getComponents()) {
        auto *worldPositionComponent = dynamic_cast<TransformComponent *>(c.get());
        if (worldPositionComponent != nullptr) {
            component.position().x() = float(worldPositionComponent->getPosition().x);
            component.position().y() = float(worldPositionComponent->getPosition().y);
            return worldPositionComponent;
        }
    }

    return nullptr;
}

void PhysicsComponent::initialize(EntityObject &entityParent) {

}

void PhysicsComponent::setTransform(Vector2 pos, float angle) {
    _physicsAPI.setTransform(_bodyId, pos, angle / 180.f * M_PI);
}

void PhysicsComponent::addForce(Vector2 dir) {
    _physicsAPI.addForce(_bodyId, dir);
}
