#include "ComponentFactory.hpp"
#include "EntityObject.hpp"
#include "../Object/CollisionHandler.hpp"
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
    return new EntityObject(entityId, EntityType::object);
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

    if (cheatMode && _physicsComponent && inputSystem.keyMap.action == "CLICK_MIDDLE") {
        _physicsComponent->setTransform(Vector2(inputSystem.x, inputSystem.y), false);
    }
}

void EntityObject::initializeComponents() {
    // Add Transform component if it doesn't exist.
    bool transformFound = false;
    if (getComponent<TransformComponent>()) {
        transformFound = true;
    }

    _physicsComponent = getComponent<PhysicsComponent>();

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

void EntityObject::setPool(Pool &pool) {
    _pool = &pool;
}

void EntityObject::destroy() {
    if (_pool == nullptr) return;
    _pool->disableEntity(*this);
}

EntityObject::EntityType EntityObject::getType(const std::string &type) {
    if (type == "character") {
        return EntityType::character;
    }

    if (type == "level_change") {
        return EntityType::level_change;
    }

    if (type == "weapon") {
        return EntityType::weapon;
    }

    if (type == "resource") {
        return EntityType::resource;
    }

    if (type == "object") {
        return EntityType::object;
    }

    throw std::invalid_argument("Type " + type + " does not exists");
}


void EntityObject::setType(const EntityType &type) {
    _type = type;
}

EntityObject::EntityType EntityObject::getType() {
    return _type;
}

void EntityObject::postInitialize(EntityObject &entityObject) {
    for (auto &comp : _components) {
        comp->postInitialize(*this);
    }
}
