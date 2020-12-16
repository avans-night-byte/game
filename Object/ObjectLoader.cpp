#include "ObjectLoader.hpp"

#include "../Game.hpp"
#include "../Components/PhysicsComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/ComponentFactory.hpp"

void ObjectLoader::loadEntities(const std::multimap<std::string, Components::component *> &loadedEntities,
                                std::vector<std::unique_ptr<EntityObject>> &entities) {
    auto componentFactory = Game::getInstance()->getComponentFactory();

    auto instantiatedEntities = std::map<std::string, EntityObject *>();
    auto entitiesPhysicsComponent = std::map<EntityObject *, Components::component *>();

    for (auto &loadedEntity : loadedEntities) {
        auto &newEntity = instantiatedEntities[loadedEntity.first];
        if (newEntity == nullptr) {
            newEntity = new EntityObject(Game::getInstance()->createEntity(), loadedEntity.first);
            entities.push_back(std::unique_ptr<EntityObject>(newEntity));

            instantiatedEntities[loadedEntity.first] = newEntity;
        }

        const auto &component = loadedEntity.second;
        const auto &componentName = component->componentName();

        if (ComponentFactory::IsPhysicsComponent(componentName)) {
            /** ContactHandler **/
            entitiesPhysicsComponent[newEntity] = component;
        } else {
            auto *newComponent = componentFactory->getComponent(newEntity->getEntityId(),
                                                                componentName,
                                                                component);
            newEntity->addComponent(newComponent);
        }
    }


    /** Contact Handlers & TransformComponent **/
    for (auto &entityPhysicsComponent : entitiesPhysicsComponent) {
        auto *resourceComponent = entityPhysicsComponent.second;
        std::vector<std::string> foundHandlerName{};

        auto *entityObject = entityPhysicsComponent.first;

        auto *transformComponent = PhysicsComponent::setPositionPhysicsResource(entityObject,
                                                                                resourceComponent->physicsComponent().get());
        auto *physicsComponent = (PhysicsComponent *) componentFactory->getComponent(entityObject->getEntityId(),
                                                                                     "PhysicsComponent",
                                                                                     resourceComponent);

        if (transformComponent) {
            const RTransform &rPosition = physicsComponent->getRTransform();
            transformComponent->refLocation(rPosition.X, rPosition.Y);
        }

        entityObject->addComponent(physicsComponent);

        getContactHandlerNames(foundHandlerName, *resourceComponent);
        if (!foundHandlerName.empty()) {
            std::vector<ContactHandler *> contactHandlers{};
            getContactHandlers(contactHandlers, entityObject, foundHandlerName);

            for (ContactHandler *handler : contactHandlers) {
                physicsComponent->contactHandlers.push_back(handler);
            }
        }
    }


    for (auto &entity : instantiatedEntities) {
        entity.second->initializeComponents();
    }
}

void ObjectLoader::getContactHandlers(std::vector<ContactHandler *> &contactHandlers,
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
                throw std::runtime_error("ContactHandler: " + handlerName + " couldn't be found!");
            }
            auto contactHandler = dynamic_cast<ContactHandler *>( foundHandler);
            if (contactHandler == nullptr) {
                throw std::runtime_error(handlerName + " does not derive from ContactHandler");
            }

            contactHandlers.push_back(contactHandler);
            break;
        }
    }
}

void ObjectLoader::getContactHandlerNames(std::vector<std::string> &names,
                                       const Components::component &component) {
    auto &physicsComponent = component.physicsComponent().get();

    for (auto &n : physicsComponent.contactHandler()) {
        names.push_back((std::string) n.c_str());
    }
}
