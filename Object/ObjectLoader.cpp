#include "ObjectLoader.hpp"

struct physicsComponents {
    std::vector<Components::component *> physicsComponents{};
};

void ObjectLoader::loadEntities(const std::vector<EntityXMLParser::ObjectData> &loadedEntities,
                                std::vector<std::unique_ptr<EntityObject>> &entities) {
    auto componentFactory = Game::getInstance()->getComponentFactory();

    auto instantiatedEntities = std::map<std::string, EntityObject *>();
    auto entitiesPhysicsXml = std::map<EntityObject *, physicsComponents>();

    for (auto &loadedEntity : loadedEntities) {
        for (auto &comp : loadedEntity.xmlComponents) {
            auto &newEntity = instantiatedEntities[loadedEntity.name];
            if (newEntity == nullptr) {
                newEntity = new EntityObject(Game::getInstance()->createEntity(), loadedEntity.name,
                                             EntityObject::getType(loadedEntity.type));
                entities.push_back(std::unique_ptr<EntityObject>(newEntity));

                instantiatedEntities[loadedEntity.name] = newEntity;
            }

            const auto &componentName = comp->componentName();

            if (ComponentFactory::IsPhysicsComponent(componentName)) {
                /** CollisionHandler **/
                entitiesPhysicsXml[newEntity].physicsComponents.push_back(comp);
            } else {
                auto *newComponent = componentFactory->getComponent(newEntity->getEntityId(),
                                                                    componentName,
                                                                    comp);
                newEntity->addComponent(newComponent);
            }
        }
    }


    /** Collision Handlers & TransformComponent **/
    for (auto &entityPhysicsComponent : entitiesPhysicsXml) {
        PhysicsComponent *newPhysicsComponent = nullptr;

        for (auto *comp : entityPhysicsComponent.second.physicsComponents) {
            auto *resourceComponent = comp->_clone();
            if(newPhysicsComponent != nullptr)
            {
                newPhysicsComponent->addFixture(resourceComponent);
                continue;
            }


            auto *entityObject = entityPhysicsComponent.first;

            auto *transformComponent = PhysicsComponent::setPositionPhysicsResource(entityObject,
                                                                                    resourceComponent->physicsComponent().get());
            newPhysicsComponent = (PhysicsComponent *) componentFactory->getComponent(entityObject->getEntityId(),
                                                                                      "PhysicsComponent",
                                                                                      resourceComponent);

            if (transformComponent) {
                const RTransform &rPosition = newPhysicsComponent->getRTransform();
                transformComponent->refLocation(rPosition.X, rPosition.Y);
            }

            entityObject->addComponent(newPhysicsComponent);

            std::vector<std::string> foundHandlerName{};
            getCollisionHandlerNames(foundHandlerName, *resourceComponent);
            if (!foundHandlerName.empty()) {
                std::vector<CollisionHandler *> collisionHandlers{};
                getCollisionHandlers(collisionHandlers, entityObject, foundHandlerName);

                for (CollisionHandler *handler : collisionHandlers) {
                    newPhysicsComponent->collisionHandlers.push_back(handler);
                }
            }
        }
    }


    for (auto &entity : instantiatedEntities) {
        entity.second->initializeComponents();
    }
}

void ObjectLoader::getCollisionHandlers(std::vector<CollisionHandler *> &collisionHandlers,
                                        EntityObject *entityObject,
                                        const std::vector<std::string> &handlerNames) {
    for (const std::string &handlerName : handlerNames) {
        for (auto &entityComponent : entityObject->getComponents()) {
            Component *foundHandler = nullptr;

            if (entityComponent->name() != handlerName) {
                continue;
            }

            foundHandler = entityComponent.get();

            if (foundHandler == nullptr) {
                throw std::runtime_error("CollisionHandler: " + handlerName + " couldn't be found!");
            }
            auto contactHandler = dynamic_cast<CollisionHandler *>( foundHandler);
            if (contactHandler == nullptr) {
                throw std::runtime_error(handlerName + " does not derive from CollisionHandler");
            }

            collisionHandlers.push_back(contactHandler);
            break;
        }
    }
}

void ObjectLoader::getCollisionHandlerNames(std::vector<std::string> &names,
                                            const Components::component &component) {
    auto &physicsComponent = component.physicsComponent().get();

    for (auto &n : physicsComponent.collisionHandler()) {
        names.push_back((std::string) n.c_str());
    }
}
