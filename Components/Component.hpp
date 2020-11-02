#pragma once

#include <map>

typedef unsigned long EntityId;
typedef int PlayerId;

class Component {
protected:
    EntityId owner;
public:
    virtual void update() = 0;

    Component(EntityId id) : owner(id) {}

    virtual ~Component() {}
};

template<typename C>
class System {
public:
    std::multimap<EntityId, C *> components;
};