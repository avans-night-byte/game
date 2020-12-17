#pragma once

#include "../Components/EntityObject.hpp"
#include "GlobalObjects.hpp"

#include <type_traits>
#include <stdexcept>
#include <vector>

class Pool {
private:
    EntityId _id{};
    std::string _entityName;

    std::vector<std::unique_ptr<EntityObject>> _pool;

    int currentIndex = 0;
    int amountSpawned = 0;
    int size = 0;

public:
    Pool() = default;

    [[nodiscard]] inline const std::string &getEntityName() const {
        return _entityName;
    }
    std::vector<EntityObject*> entitiesInUse;


public:
    void initialize(const std::string& loadList, const std::string& entityName, int startAmount);

    void resetEntities();

    EntityObject* getEntity();
};

