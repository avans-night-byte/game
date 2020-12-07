#include <Generated/level-resources.hxx>
#include "../Game.hpp"
#include "../../API/RPosition.hpp"


#include "PhysicsComponent.hpp"


void PhysicsComponent::update() {

}

void PhysicsComponent::fixedUpdate(const float &deltaTime) {

}

PhysicsComponent::PhysicsComponent(EntityId id)
        : Component(id), enginePhysicsAPI(Game::getInstance()->getPhysicsAPI()) {

}

PhysicsComponent::PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, Vector2 size)
        : Component(id),
          enginePhysicsAPI(Game::getInstance()->getPhysicsAPI()),
          bodyId{this->initializeBoxBody(bodyType, position, size)} {


}

PhysicsComponent::PhysicsComponent(EntityId id, BodyType bodyType, Vector2 position, float radius)
        : Component(id),
          enginePhysicsAPI(Game::getInstance()->getPhysicsAPI()),
          bodyId(this->initializeCircleBody(bodyType, position, radius)) {


}

string PhysicsComponent::name() const {
    return "PhysicsComponent";
}



Component *PhysicsComponent::Clone(EntityId entityId, const LevelResources::component *component) {
    auto &resourcePhysicsComponent = component->physicsComponent().get();
    auto bodyTypeString = std::string(resourcePhysicsComponent.bodyType().c_str());

    auto &shapeCircle = resourcePhysicsComponent.bodyShape().circle();
    auto &shapeBox = resourcePhysicsComponent.bodyShape().box();


    BodyType bodyType = StringToBodyType(bodyTypeString);


    /* Shape */
    PhysicsComponent *newPhysicsComponent = nullptr;
    if(shapeCircle != nullptr)
    {
        auto position = Vector2(shapeCircle->positionF().x(), shapeCircle->positionF().y());
        newPhysicsComponent = new PhysicsComponent(entityId, bodyType, position, shapeCircle->radius());
    }
    else // Box
    {
        auto position = Vector2(shapeBox->positionF().x(), shapeBox->positionF().y());
        auto size = Vector2(shapeBox->width(), shapeBox->height());
        newPhysicsComponent = new PhysicsComponent(entityId, bodyType, position, size);
    }

    // TODO: Set Friction for physicsComponent;
    auto contactHandlerName = std::string(resourcePhysicsComponent.contactHandler().c_str());
    

    return newPhysicsComponent;
}
