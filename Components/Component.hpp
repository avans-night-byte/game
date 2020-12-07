#pragma once

#include <map>
#include <memory>

typedef unsigned long EntityId;
typedef int PlayerId;

namespace LevelResources {
    class component;
}

class Component {
protected:
    EntityId owner;

public:
    inline const EntityId &GetEntityId() {
        return owner;
    }

public:
    virtual void update() = 0;

    virtual void fixedUpdate(const float &deltaTime) = 0;

    Component(EntityId id) : owner(id) {}

    Component() {}

    virtual ~Component() {}

    virtual std::string name() const = 0;

    [[nodiscard]] virtual Component *Clone(EntityId entityId, const LevelResources::component *component) = 0;
};

template<typename C>
class System {
public:
    std::multimap<EntityId, C *> components;
};