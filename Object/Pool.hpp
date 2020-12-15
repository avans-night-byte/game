#pragma once
#include "../Components/EntityObject.hpp"
#include "../Game.hpp"

#include "queue"
#include <type_traits>
#include <stdexcept>

class Pool {
private:
    EntityId _id{};

    std::queue<EntityObject> _queue{};
    const EntityObject &_entityObject;

public:
    explicit Pool(EntityObject &entityObject) : _entityObject(entityObject) {

    }

    template<class T>
    void initialize() {
        static_assert(std::is_base_of<Component, T>::value);

        if (_entityObject.getComponent<T>() == nullptr) {
            throw std::runtime_error(_entityObject.name() + " does not contain component: " + typeid(T).name());
        }

        // TODO: Instantiate objects from here
    }
};