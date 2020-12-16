#pragma once

#include "../Components/EntityObject.hpp"
#include "GlobalObjects.hpp"

#include <type_traits>
#include <stdexcept>
#include <vector>

class Pool {
private:
    EntityId _id{};

    std::vector<std::unique_ptr<EntityObject>> _pool;
    int currentIndex = 0;
    int size;

public:
    template<class T>
    void initialize(const std::string& loadList, const std::string& entityName, int startAmount){
        static_assert(std::is_base_of<Component, T>::value);

        this->size = startAmount;
        auto entity = GlobalObjects::getInstance()->loadEntity(loadList, entityName);
        if (entity->getComponent<T>() == nullptr) {
            throw std::runtime_error(entity->name() + " does not contain component: " + typeid(T).name());
        }
        GlobalObjects::getInstance()->loadEntities(_pool, loadList, entityName, startAmount);
    }

    EntityObject* getEntity();
};

