#include "ComponentFactory.hpp"
#include "EntityObject.hpp"
#include "Rendering/RenderComponent.hpp"
#include "TransformComponent.hpp"
#include "PhysicsComponent.hpp"

std::string EntityObject::name() const {
    return "EntityObject";
}

void EntityObject::fixedUpdate(const float &deltaTime) {
    for (auto &component : _components) {
        component->fixedUpdate(deltaTime);
    }
}

void EntityObject::addComponent(Component *component) {
    _components.push_back(std::unique_ptr<Component>(component));
}

Component *EntityObject::build(EntityId entityId, const Components::component *component) {
    return new EntityObject(entityId);
}

void EntityObject::render() {
    for (auto &component : _components) {
        component->render();
    }
}

void EntityObject::update(const Input &inputSystem) {
    for (auto &component : _components) {
        component->update(inputSystem);
    }
}

void EntityObject::initializeComponents() {
    // Add Transform component if it doesn't exist.
    bool transformFound = false;
    if (getComponent<TransformComponent>()) {
        transformFound = true;
    }

    if (!transformFound) {
        auto *pTransformComponent = Game::getInstance()
                ->getComponentFactory()->getComponent<TransformComponent>(getEntityId());
        addComponent((Component *) pTransformComponent);
    }

    for (auto &comp : _components) {
        comp->initialize(*this);
    }
}

void EntityObject::initialize(EntityObject &entityParent) {

}

TransformComponent *EntityObject::getTransform() {
    if (!_transformComponent)
        _transformComponent = getComponent<TransformComponent>();

    if (!_transformComponent)
        throw std::runtime_error("Entity must have transform component");

    return _transformComponent;
}

PhysicsComponent *EntityObject::getPhysicsComponent() {
    if (!_physicsComponent)
        _physicsComponent = getComponent<PhysicsComponent>();

    return _physicsComponent;
}

Component *EntityObject::getComponent(std::string componentName) {
    for (auto &comp : _components) {
        if (comp->name() == componentName) {
            return comp.get();
        }
    }

    return nullptr;
}
