#pragma once
#include "../Components/EntityObject.hpp"
#include "../Game.hpp"

#include "queue"
#include <type_traits>
#include <stdexcept>

template<class T>
class PoolingSystem {
public:
    explicit PoolingSystem(EntityObject &entityObject) : _entityObject(entityObject) {
        static_assert(std::is_base_of<Component, T>::value);

        if (entityObject.getComponent<T>() == nullptr) {
            throw std::runtime_error(entityObject.name() + " does not contain component: " + typeid(T).name());
        }
    }

    void initialize() {

    }


private:
    EntityId _id{};
    std::queue<EntityObject> _queue{};
    const EntityObject &_entityObject;
};