#pragma once

#include <map>
#include <vector>
#include <string>
#include <mutex>
#include <memory>

#include "../../API/XMLParser/LevelParserAPI.hpp"

namespace Components {
    class component;
}
class EntityObject;

class GlobalObjects {
private:
    static GlobalObjects *_instance;
    static std::mutex _mutex;

    std::map<std::string, std::vector<EntityXMLParser::ObjectData>> _objectsLists{};
public:
    static GlobalObjects *getInstance();

    void initializeObjects(const std::string &name, const std::string &path, const std::string &poolName,
                           const std::string &poolPath);

    std::unique_ptr<EntityObject> loadEntity(const std::string &fromList, const std::string &entityName);

    void loadEntities(std::vector<std::unique_ptr<EntityObject>> &entities, const std::string &fromList,
                      const std::string &entityName, int amount);
private:
    static void getObjectFromLoader(const std::vector<EntityXMLParser::ObjectData> &loadedEntities,
                             std::vector<std::unique_ptr<EntityObject>> &entities, int amount);

    void loadEntities(std::vector<EntityXMLParser::ObjectData> &loadedObjectData, const std::string &path,
                      const std::string &name);
};

