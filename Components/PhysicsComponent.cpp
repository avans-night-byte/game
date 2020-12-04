#include "PhysicsComponent.hpp"

#include "../Game.hpp"

void PhysicsComponent::update() {

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

unique_ptr<Component> PhysicsComponent::Clone(EntityId entityId) {


    return std::unique_ptr<Component>();
}
