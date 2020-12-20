#include <iostream>
#include "Pool.hpp"
#include "../Components/PhysicsComponent.hpp"


EntityObject *Pool::getEntity() {
    if (++currentIndex >= size) {
        std::cout << "Reached _pool size" << std::endl;
        currentIndex = 0;
    }

    auto *entity = _pool.at(currentIndex).get();

    if (amountSpawned < _pool.size())
        entitiesInUse.push_back(entity);
    else
        amountSpawned++;

    return entity;
}

void Pool::initialize(const std::string &loadList, const std::string &entityName, int startAmount) {
    this->_entityName = std::string(entityName);
    this->size = startAmount;

    GlobalObjects::getInstance()->loadEntities(_pool, loadList, entityName, startAmount);
}

void Pool::resetEntities() {
    for (auto &entity: _pool) {
        for (auto &comp : entity->getComponents()) {
            if (auto *physicsComponent = dynamic_cast<PhysicsComponent *>(comp.get())) {
                physicsComponent->setEnabled(false);
            }
        }
    }

    this->currentIndex = 0;
    this->amountSpawned = 0;
    this->entitiesInUse.clear();
}
