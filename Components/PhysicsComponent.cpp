#include <Generated/level-resources.hxx>
#include <memory>
#include "../Game.hpp"

#include "PhysicsComponent.hpp"
#include "TransformComponent.hpp"
#include "../../Engine/Physics/PhysicsEngineAdapter.hpp"


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

std::string PhysicsComponent::name() const {
    return "PhysicsComponent";
}

Component *PhysicsComponent::build(EntityId entityId,
                                   const Components::component *component) {

    auto newPhysicsComponent = new PhysicsComponent(entityId);
    auto &physicsComponent = component->physicsComponent().get();
    auto bodyTypeString = std::string(physicsComponent.bodyType().c_str());

    auto &shapeCircle = physicsComponent.bodyShape().circle();
    auto &shapeBox = physicsComponent.bodyShape().box();


    BodyType bodyType = StringToBodyType(bodyTypeString);
    Vector2 position = Vector2(physicsComponent.position().x(), physicsComponent.position().y());
    bool isEnabled = physicsComponent.isEnabled().present() ? physicsComponent.isSensor().get()
                                                            : Components::physicsComponent::isEnabled_default_value();

    std::unique_ptr<Box2DData> box2DData = std::make_unique<Box2DData>();
    box2DData->position = position;
    box2DData->bodyType = bodyType;
    box2DData->isEnabled = isEnabled;
    box2DData->isSensor = physicsComponent.isSensor().present() ? physicsComponent.isSensor().get()
                                                                : Components::physicsComponent::isSensor_default_value();

    box2DData->isBullet = physicsComponent.isBullet().present() ? physicsComponent.isBullet().get()
                                                                : Components::physicsComponent::isBullet_default_value();
    box2DData->userData = newPhysicsComponent;

    /* Shape */
    if (shapeCircle != nullptr) {
        std::unique_ptr<Box2DCircleData> circleData((Box2DCircleData *) box2DData.release());

        circleData->radius = shapeCircle->radius();
        newPhysicsComponent->_bodyId = _physicsAPI.createBody(*circleData.release());
    } else {
        // BOX
        std::unique_ptr<Box2DBoxData> boxData((Box2DBoxData *) box2DData.release());

        boxData->size = Vector2(shapeBox->width(), shapeBox->height());

        newPhysicsComponent->_bodyId = _physicsAPI.createBody(*boxData.release());
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
    _physicsAPI.setAngle(_bodyId, angle);
}

void PhysicsComponent::destroyBody() {
    _physicsAPI.destroyBody(_bodyId);
}

TransformComponent *
PhysicsComponent::setPositionPhysicsResource(EntityObject *pObject, Components::physicsComponent &component) {
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

void PhysicsComponent::setEnabled(bool b) {
    _physicsAPI.setEnabled(_bodyId, b);
}

