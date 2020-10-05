//
// Created by sasch on 05/10/2020.
//

#ifndef NIGHTBYTE_COMPONENT_HPP
#define NIGHTBYTE_COMPONENT_HPP


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

template <typename C> class System {
public:
    std::multimap<EntityId, C * > components;
};


#endif //NIGHTBYTE_COMPONENT_HPP
