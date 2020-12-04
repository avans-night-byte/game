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

    virtual std::string name() const = 0;

    virtual Component *Clone(EntityId entityId) const = 0;
};

template<typename C>
class System {
public:
    std::multimap<EntityId, C *> components;
};