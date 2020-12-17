#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

namespace Components {
    class component;
}
class EntityObject;
class ContactHandler;

class ObjectLoader {
public:
    static void loadEntities(const std::multimap<std::string, Components::component *> &loadedEntities,
                      std::vector<std::unique_ptr<EntityObject>> &entities);

private:
    static void getContactHandlers(std::vector<ContactHandler *> &contactHandlers, EntityObject *entityObject,
                            const std::vector<std::string> &handlerNames);

    static void getContactHandlerNames(std::vector<std::string> &names, const Components::component &component);
};