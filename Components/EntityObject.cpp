#include "ComponentFactory.hpp"
#include "EntityObject.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"

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

Component *EntityObject::build(EntityId entityId, const Components::component *component) {
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
        if (getComponent<TransformComponent>()) {
            transformFound = true;
            break;
        }
    }

    if (!transformFound) {
        auto *pTransformComponent = Game::getInstance()
                ->getComponentFactory()->getComponent<TransformComponent>(getEntityId());
        addComponent((Component *) pTransformComponent);
    }

    for (auto &comp : components) {
        comp->initialize(*this);
    }
}

void EntityObject::initialize(EntityObject &entityParent) {

}

TransformComponent *EntityObject::getTransform() {
    if (!transformComponent)
        transformComponent = getComponent<TransformComponent>();

    if (!transformComponent)
        throw std::runtime_error("Entity must have transform component");

    return transformComponent;
}

PhysicsComponent *EntityObject::getPhysicsComponent() {
    if (!physicsComponent)
        physicsComponent = getComponent<PhysicsComponent>();

    return physicsComponent;
}

Component *EntityObject::getComponent(std::string componentName) {
    for (auto &comp : components) {
        if (comp->name() == componentName) {
            return comp.get();
        }
    }

    return nullptr;
}
