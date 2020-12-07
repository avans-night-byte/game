#include "EntityObject.hpp"

void EntityObject::update() {

}

std::string EntityObject::name() const {
    return "EntityObject";
}

void EntityObject::fixedUpdate(const float &deltaTime) {

}

void EntityObject::AddComponent(Component *component) {
    components.push_back(std::unique_ptr<Component>(component));
}

Component *EntityObject::Clone(EntityId entityId, const LevelResources::component *component) {
    return new EntityObject(entityId);
}
