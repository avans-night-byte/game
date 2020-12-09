#include "EntityObject.hpp"

void EntityObject::update() {

}

std::string EntityObject::name() const {
    return "EntityObject";
}

void EntityObject::fixedUpdate(const float &deltaTime) {

}

void EntityObject::addComponent(Component *component) {
    components.push_back(std::unique_ptr<Component>(component));
}

Component *EntityObject::clone(EntityId entityId, const Components::component *component) {
    return new EntityObject(entityId);
}
