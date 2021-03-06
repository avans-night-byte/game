#pragma once

#include <map>
#include <memory>


typedef unsigned long EntityId;
typedef int PlayerId;

namespace Components {
    class component;
}
class Input;
class EntityObject;

class Component {
protected:
    EntityId owner;

public:
    Component(EntityId id, Component& component) {
        component.owner = id;
    }

    const EntityId getEntityId() {
        return owner;
    }

public:
    virtual void render() = 0;

    virtual void update(const Input &inputSystem) = 0;

    virtual void fixedUpdate(const float &deltaTime) = 0;

    Component(EntityId id) : owner(id) {}

    Component() {}

    virtual ~Component() {}

    virtual std::string name() const = 0;

    virtual Component *build(EntityId entityId, const Components::component *component) = 0;

    virtual void initialize(EntityObject &entityParent) = 0;

    virtual void postInitialize(EntityObject &entityObject) = 0;
};

template<typename C>
class System {
public:
    std::multimap<EntityId, C *> components;
};