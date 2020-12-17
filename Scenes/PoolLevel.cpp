#include "PoolLevel.hpp"

#include <iostream>

void PoolLevel::initialize(const std::string &name, const LevelData &data) {

}

void PoolLevel::render() {
    for (auto &pool : _poolList) {
        for (auto &entity : pool->entitiesInUse) {
            entity->render();
        }
    }
}

void PoolLevel::update(const Input &inputSystem) {
    for (auto &pool : _poolList) {
        for (auto &entity : pool->entitiesInUse) {
            entity->update(inputSystem);
        }
    }
}

void PoolLevel::fixedUpdate(float deltaTime) {
    for (auto &pool : _poolList) {
        for (auto &entity : pool->entitiesInUse) {
            entity->fixedUpdate(deltaTime);
        }
    }
}

void PoolLevel::destroyAllBodies() {
}

void PoolLevel::clearEntities() {
}

void PoolLevel::addPool(const std::string &loadList, const std::string &entityName, int startAmount) {
    if (entityName.find(entityName) == -1) {
        std::cout << "Entity of name: '" + entityName + "' already used for _pool" << std::endl;
        return;
    }

    auto pool = std::make_unique<Pool>();
    pool->initialize(loadList, entityName, startAmount);

    _poolList.push_back(std::move(pool));
    _loadedEntities.push_back(entityName);
}

Pool &PoolLevel::getPool(const std::string &poolName) {
    for (auto &pool : _poolList) {
        if (pool->getEntityName() == poolName) {
            return *pool;
        }
    }

    throw std::runtime_error("Pool of entity: '" + poolName + "' does not exists");
}