#include "EntityObject.hpp"

std::string EntityObject::name() const {
    return "EntityObject";
}

void EntityObject::fixedUpdate(const float &deltaTime) {
    for(auto &component : components)
    {
        component->fixedUpdate(deltaTime);
    }
}

void EntityObject::addComponent(Component *component) {
    components.push_back(std::unique_ptr<Component>(component));
}

Component *EntityObject::clone(EntityId entityId, const Components::component *component) {
    return new EntityObject(entityId);
}

void EntityObject::render() {
    for(auto &component : components)
    {
        component->render();
    }
}

void EntityObject::update(const Input &inputSystem) {
    for(auto &component : components)
    {
        component->update(inputSystem);
    }
}
