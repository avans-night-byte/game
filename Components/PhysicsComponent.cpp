#include "../Game.hpp"

#include "TransformComponent.hpp"
#include "../Object/CollisionHandler.hpp"
#include "../Components/EntityObject.hpp"
#include <b2_contact.h>

#include <memory>

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

    auto *box2DData = new Box2DData();
    box2DData->position = position;
    box2DData->bodyType = bodyType;
    box2DData->isEnabled = physicsComponent.isEnabled().present() ? physicsComponent.isEnabled().get()
                                                                  : Components::physicsComponent::isEnabled_default_value();

    box2DData->isSensor = physicsComponent.isSensor().present() ? physicsComponent.isSensor().get()
                                                                : Components::physicsComponent::isSensor_default_value();

    box2DData->isBullet = physicsComponent.isBullet().present() ? physicsComponent.isBullet().get()
                                                                : Components::physicsComponent::isBullet_default_value();

    box2DData->isRotationLocked = physicsComponent.isRotationLocked().present() ? physicsComponent.isRotationLocked().get()
                                                                : Components::physicsComponent::isRotationLocked_default_value();
    box2DData->contactHandler = newPhysicsComponent;

    /* Shape */
    if (shapeCircle != nullptr) {
        std::unique_ptr<Box2DCircleData> circleData(new Box2DCircleData(*box2DData));

        circleData->radius = shapeCircle->radius();
        newPhysicsComponent->_bodyId = _physicsAPI.createBody(*circleData);
    } else {
        // BOX
        std::unique_ptr<Box2DBoxData> boxData(new Box2DBoxData(*box2DData));

        boxData->size = Vector2(shapeBox->width(), shapeBox->height());

        newPhysicsComponent->_bodyId = _physicsAPI.createBody(*boxData);
    }

    delete box2DData;
    return newPhysicsComponent;
}

void PhysicsComponent::startContact(b2Contact *contact, bool isA) {
    PhysicsComponent *self = nullptr;
    PhysicsComponent *other = nullptr;
    if (isA) {
        self = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureA()->GetBody()->GetUserData().contactHandler);
        other = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureB()->GetBody()->GetUserData().contactHandler);
    } else {
        self = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureB()->GetBody()->GetUserData().contactHandler);
        other = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureA()->GetBody()->GetUserData().contactHandler);
    }

    for (int i = 0; i < this->collisionHandlers.size(); i++) {
        EntityObject *otherParent = other ? other->getParent() : nullptr;
        collisionHandlers[i]->onCollisionEnter(self->getParent(), otherParent);
    }
}

void PhysicsComponent::endContact(b2Contact *contact, bool isA) {
    PhysicsComponent *self = nullptr;
    PhysicsComponent *other = nullptr;
    if (isA) {
        self = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureA()->GetBody()->GetUserData().contactHandler);
        other = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureB()->GetBody()->GetUserData().contactHandler);
    } else {
        self = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureB()->GetBody()->GetUserData().contactHandler);
        other = dynamic_cast<PhysicsComponent *>((PhysicsComponent *) contact->GetFixtureA()->GetBody()->GetUserData().contactHandler);
    }

    for (int i = 0; i < this->collisionHandlers.size(); i++) {
        EntityObject *otherParent = other ? other->getParent() : nullptr;
        collisionHandlers[i]->onCollisionExit(self->getParent(), otherParent);
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
    this->_parent = &entityParent;
}

void PhysicsComponent::setTransform(Vector2 pos, float angle) {
    _physicsAPI.setTransform(_bodyId, pos, angle / 180.f * M_PI);
}

void PhysicsComponent::addForce(const Vector2 &position, Vector2 force) {
    _physicsAPI.addForce(_bodyId, position, force);
}

void PhysicsComponent::setEnabled(bool b) {
    _physicsAPI.setEnabled(_bodyId, b);
}

// TODO: Only supports box fixtures
void PhysicsComponent::addFixture(Components::component *pComponent) {
    auto &physicsComponent = pComponent->physicsComponent().get();

    auto &box = physicsComponent.bodyShape().box().get();
    float &width = box.width();
    float &height = box.height();
    float &offsetX = box.offsetX().get();
    float &offsetY = box.offsetY().get();


    Box2DBoxData box2DBoxData;
    box2DBoxData.offset = Vector2(offsetX, offsetY);
    box2DBoxData.size = Vector2(width, height);
    box2DBoxData.isSensor = physicsComponent.isSensor().present() ? physicsComponent.isSensor().get()
                                                                  : Components::physicsComponent::isSensor_default_value();

    this->_physicsAPI.addFixture(_bodyId, box2DBoxData);
}

void PhysicsComponent::postInitialize(EntityObject &entityObject) {

}
