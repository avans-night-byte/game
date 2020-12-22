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
    for (auto &entity : _pool) {
        entity->setPool(*this);
    }
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

void Pool::disableEntity(EntityObject &pObject) {
   auto it = std::find(entitiesInUse.begin(), entitiesInUse.end(), &pObject);
   if(it != entitiesInUse.end()){
       int index = std::distance(entitiesInUse.begin(), it);
       entitiesInUse[index]->getComponent<PhysicsComponent>()->setEnabled(false);
       entitiesInUse.erase(it);

       auto it2 = std::find_if(_pool.begin(), _pool.end(), [&](std::unique_ptr<EntityObject>& p){
           return p.get() == &pObject;
       });

       if(it2 != _pool.end()){
           _pool.push_back(std::move(*it2));
           _pool.erase(it2);
           amountSpawned--;
       }
   }
}
