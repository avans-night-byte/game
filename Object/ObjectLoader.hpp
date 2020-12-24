#pragma once

#include <map>
#include <string>
#include <vector>
#include <memory>

#include "../Components/PhysicsComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ComponentFactory.hpp"
#include "../Object/CollisionHandler.hpp"

namespace Components {
    class component;
}
class EntityObject;
class CollisionHandler;

class ObjectLoader {
public:
    static void loadEntities(const std::vector<EntityXMLParser::ObjectData> &loadedEntities,
                      std::vector<std::unique_ptr<EntityObject>> &entities);

private:
    static void getCollisionHandlers(std::vector<CollisionHandler *> &collisionHandlers, EntityObject *entityObject,
                                     const std::vector<std::string> &handlerNames);

    static void getCollisionHandlerNames(std::vector<std::string> &names, const Components::component &component);
};