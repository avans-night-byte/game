#include "GlobalObjects.hpp"

#include "../Components/EntityObject.hpp"
#include "../Scenes/PoolLevel.hpp"
#include "ObjectLoader.hpp"


#include "Generated/objects.hxx"

#include <memory>
#include <iostream>

GlobalObjects *GlobalObjects::_instance{};
std::mutex GlobalObjects::_mutex;

GlobalObjects *GlobalObjects::getInstance() {
    std::lock_guard<std::mutex> lock(_mutex);
    if (_instance == nullptr) {
        _instance = new GlobalObjects();
    }

    return _instance;
}

void GlobalObjects::initializeObjects(const std::string &name,
                                      const std::string &path,
                                      const std::string &poolName,
                                      const std::string &poolPath) {
    if (_objectsLists.find(name) != _objectsLists.end()) {
        std::cout << "Skipping: '" + name + "', already loaded" << std::endl;
    }
    if (_objectsLists.find(poolName) != _objectsLists.end()) {
        std::cout << "Skipping: '" + poolName + "', already loaded" << std::endl;
    }

    try {
        std::vector<EntityXMLParser::ObjectData> loadedEntities{};
        loadEntities(loadedEntities, path, name);

        std::vector<EntityXMLParser::ObjectData> loadedEntitiesPool{};
        loadEntities(loadedEntitiesPool, poolPath, poolName);

        for (auto &obj: loadedEntitiesPool) {
            PoolLevel *poolLevel = Game::getInstance()->getPoolLevel();
            poolLevel->addPool(poolName, obj.name, 50); // TODO: Magic number could be replaced by XML.
        }
    } catch (const xml_schema::exception &e) {
        std::cout << e << std::endl;
    }
}

void GlobalObjects::loadEntities(std::vector<EntityXMLParser::ObjectData> &loadedObjectData, const std::string &path,
                                 const std::string &name) {
    auto objectList = Objects::objectList_(std::string(path));
    LevelParserAPI::loadEntities(loadedObjectData, objectList->object());
    _objectsLists[name] = loadedObjectData;

    for (auto &resource : objectList->preloadResources().resource()) {
        ResourceManager::getInstance()->loadResource(resource);
    }
}

std::unique_ptr<EntityObject>
GlobalObjects::loadEntity(const std::string &fromList, const std::string &entityName) {
    auto map = _objectsLists.find(fromList);
    if (map == _objectsLists.end())
        throw std::runtime_error(fromList + " does not exist in the global list");

    // Check if entityName corresponds to any objects
    EntityXMLParser::ObjectData objectData{"", ""};
    for (auto &object : map->second) {
        if (object.name == entityName) {
            objectData = object;
            break;
        }
    }

    if (objectData.name.empty())
        throw std::runtime_error(entityName + " does not exist in " + fromList);

    std::vector<std::unique_ptr<EntityObject>> entities{};
    getObjectFromLoader({objectData},
                        entities,
                        1);
    return std::move(entities.at(0));
}

void GlobalObjects::loadEntities(std::vector<std::unique_ptr<EntityObject>> &entities,
                                 const std::string &fromList,
                                 const std::string &entityName,
                                 int amount) {
    auto map = _objectsLists.find(fromList);
    if (map == _objectsLists.end())
        throw std::runtime_error(fromList + " does not exist in the global list");

    EntityXMLParser::ObjectData objectData{"", ""};
    for (auto &object : map->second) {
        if (object.name == entityName) {
            objectData = object;
            break;
        }
    }

    if (objectData.name.empty())
        throw std::runtime_error(entityName + " does not exist in " + fromList);


    getObjectFromLoader({objectData},
                        entities,
                        amount);
}

void GlobalObjects::getObjectFromLoader(const std::vector<EntityXMLParser::ObjectData> &loadedEntities,
                                        std::vector<std::unique_ptr<EntityObject>> &entities, int amount) {
    for (int i = 0; i < amount; ++i) {
        ObjectLoader::loadEntities(loadedEntities, entities);
    }
}