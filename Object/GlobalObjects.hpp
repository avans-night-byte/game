#pragma once

#include <map>
#include <vector>
#include <string>
#include <mutex>
#include <memory>

namespace Components {
    class component;
}
class EntityObject;

class GlobalObjects {
private:
    static GlobalObjects *_instance;
    static std::mutex _mutex;

    std::map<std::string, std::multimap<std::string, Components::component *>> _objectsLists{};
public:
    static GlobalObjects *getInstance();

    void initializeObjects(const std::string &name, const std::string &path);

    std::unique_ptr<EntityObject> getLoadedEntity(const std::string &fromList, const std::string &entityName);

    std::vector<std::unique_ptr<EntityObject>>
    getLoadedEntity(const std::string &fromList, const std::string &entityName, int amount);

private:
    static void getObjectFromLoader(const std::multimap<std::string, Components::component *> &loadedEntities,
                             std::vector<std::unique_ptr<EntityObject>> &entities, int amount);


};