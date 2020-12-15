#include "GlobalObjects.hpp"

#include "Generated/objects.hxx"
#include "../../API/XMLParser/LevelParserAPI.hpp"
#include "../Components/EntityObject.hpp"
#include "ObjectLoader.hpp"

#include <memory>

GlobalObjects *GlobalObjects::_instance{};
std::mutex GlobalObjects::_mutex;

GlobalObjects *GlobalObjects::getInstance() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_instance == nullptr) {
        _instance = new GlobalObjects();
    }

    return _instance;
}

void GlobalObjects::initializeObjects(const std::string &name, const std::string &path) {
    if (_objectsLists.find(name) != _objectsLists.end())
        throw std::runtime_error("ObjectList: '" + name + "' already exists!");

    auto objectList = Objects::objectList_(path);
    std::multimap<std::string, Components::component *> loadedEntities;
    LevelParserAPI::loadEntities(loadedEntities, objectList->object());


    _objectsLists[name] = loadedEntities;
}

std::unique_ptr<EntityObject>
GlobalObjects::getLoadedEntity(const std::string &fromList, const std::string &entityName) {
    auto map = _objectsLists.find(fromList);
    if (map == _objectsLists.end())
        throw std::runtime_error(fromList + " does not exist in the global list");

    if (map->second.find(entityName) == map->second.end())
        throw std::runtime_error(entityName + " does not exist in " + fromList);

    // Make a map with every loaded component for entityName
    auto entityIt = map->second.equal_range(entityName);
    std::multimap<std::string, Components::component *> entityToLoad{};
    for (auto &it = entityIt.first; it != entityIt.second; it++) {
        auto pair = std::make_pair(entityName, it->second);
        entityToLoad.insert(pair);
    }

    std::vector<std::unique_ptr<EntityObject>> entities{};
    getObjectFromLoader(entityToLoad,
                        entities,
                        1);
    return std::move(entities.at(0));
}

std::vector<std::unique_ptr<EntityObject>>
GlobalObjects::getLoadedEntity(const std::string &fromList, const std::string &entityName, int amount) {
    auto map = _objectsLists.find(fromList);
    if (map == _objectsLists.end())
        throw std::runtime_error(fromList + " does not exist in the global list");

    // Make a map with every loaded component for entityName
    auto entityIt = map->second.equal_range(entityName);
    std::multimap<std::string, Components::component *> entityToLoad{};
    for (auto &it = entityIt.first; it != entityIt.second; it++) {
        auto pair = std::make_pair(entityName, it->second);
        entityToLoad.insert(pair);
    }

    std::vector<std::unique_ptr<EntityObject>> entities{};
    getObjectFromLoader(entityToLoad,
                        entities,
                        amount);
    return entities;
}

void GlobalObjects::getObjectFromLoader(const std::multimap<std::string, Components::component *> &loadedEntities,
                                        std::vector<std::unique_ptr<EntityObject>> &entities, int amount) {
    for (int i = 0; i < amount; ++i) {
        ObjectLoader::loadEntities(loadedEntities, entities);
    }
}