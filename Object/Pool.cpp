#include <iostream>
#include "Pool.hpp"


EntityObject *Pool::getEntity() {
    if (++currentIndex >= size) {
        std::cout << "Reached _pool size" << std::endl;
        currentIndex = 0;
    }

    auto *entity = _pool.at(currentIndex).get();

    if (amountSpawned < _pool.size() + 1)
        entitiesInUse.push_back(entity);
    else
        amountSpawned++;

    return entity;
}

void Pool::initialize(const std::string &loadList, const std::string &entityName, int startAmount) {
    this->_entityName = std::string(entityName);
    this->size = startAmount;

    auto entity = GlobalObjects::getInstance()->loadEntity(loadList, entityName);
    GlobalObjects::getInstance()->loadEntities(_pool, loadList, entityName, startAmount);
}
