#include "ComponentFactory.hpp"
#include "EntityObject.hpp"
#include "RenderComponent.hpp"
#include "../Game.hpp"
#include "TransformComponent.hpp"

std::string EntityObject::name() const {
    return "EntityObject";
}

void EntityObject::fixedUpdate(const float &deltaTime) {
    for (auto &component : components) {
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
    for (auto &component : components) {
        component->render();
    }
}

void EntityObject::update(const Input &inputSystem) {
    for (auto &component : components) {
        component->update(inputSystem);
    }
}

void EntityObject::initializeComponents() {
    // Add Transform component if it doesn't exist.
    bool transformFound = false;
    for (auto &comp: components) {
        if (auto *transform = getComponent<TransformComponent>()) {
            transformFound = true;
            break;
        }
    }

    if (!transformFound) {
        auto *componentFactory = Game::getInstance()
                ->getComponentFactory()->getComponent<TransformComponent>(getEntityId());
        addComponent((Component*)componentFactory);
    }

    for (auto &comp : components) {
        comp->initialize(*this);
    }
}

void EntityObject::initialize(EntityObject &entityParent) {

}