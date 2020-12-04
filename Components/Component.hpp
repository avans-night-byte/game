#pragma once

#include <map>
#include <memory>

typedef unsigned long EntityId;
typedef int PlayerId;

class Component {
protected:
    EntityId owner;
public:
    virtual void update() = 0;

    Component(EntityId id) : owner(id) {}

    Component() {}

    virtual ~Component() {}

    virtual std::unique_ptr<Component> Clone(EntityId entityId) = 0;
};

template<typename C>
class System {
public:
    std::multimap<EntityId, C *> components;
};