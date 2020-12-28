#include <iostream>
#include "Pool.hpp"
#include "../Components/PhysicsComponent.hpp"


EntityObject & Pool::getEntity() {
    if (_pool.empty()) {
        enlargePool();
        std::cout << "Made '" + _entityName + "' pool bigger" << std::endl;
    }

    auto *entity = _pool.back();
    entitiesInUse.push_back(entity);
    _pool.pop_back();

    return *entity;
}

void Pool::initialize(const std::string &loadList, const std::string &entityName, int startAmount) {
    this->_loadedFromList = std::string(loadList);
    this->_entityName = std::string(entityName);
    this->_size = startAmount;

    GlobalObjects::getInstance()->loadEntities(_objects, loadList, entityName, startAmount);
    for (auto &entity : _objects) {
        _pool.push_back(entity.get());
        entity->setPool(*this);
    }
}

void Pool::enlargePool() {
    GlobalObjects::getInstance()->loadEntities(_objects,
                                               _loadedFromList,
                                               _entityName,
                                               10);
    this->_size += 10;
    for (auto item = _objects.end() - 10; item != _objects.end(); item++) {
        _pool.push_back(item->get());
        item->get()->postInitialize(*item->get());
        item->get()->setPool(*this);
    }
}

void Pool::resetEntities() {
    for (auto &entity: _objects) {
        if (auto *physicsComponent = entity->getComponent<PhysicsComponent>()) {
            physicsComponent->setEnabled(false);
        }
    }

    _pool.clear();
    this->entitiesInUse.clear();

    for (auto &entity : _objects) {
        _pool.push_back(entity.get());
    }
}

void Pool::disableEntity(EntityObject &pObject) {
    auto it = std::find(entitiesInUse.begin(), entitiesInUse.end(), &pObject);
    if (it != entitiesInUse.end()) {
        (*it)->getComponent<PhysicsComponent>()->setEnabled(false);

        _pool.push_back(*it);
        entitiesInUse.erase(it);
    }
}
