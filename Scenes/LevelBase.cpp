#include "LevelBase.hpp"

#include "../Components/EntityObject.hpp"
#include "../Components/ComponentFactory.hpp"
#include "Generated/level-resources.hxx"
#include "../Components/PhysicsComponent.hpp"
#include "../ContactHandlers/ExplosionCrate.hpp"

void LevelBase::LoadEntities(const std::multimap<std::string, const Components::component *> &loadedEntities) {
    auto componentFactory = Game::getInstance()->getComponentFactory();

    auto instantiatedEntities = std::map<std::string, EntityObject *>();
    auto entitiesPhysicsComponent = std::map<EntityObject *, const Components::component *>();

    for (auto &loadedEntity : loadedEntities) {
        auto &newEntity = instantiatedEntities[loadedEntity.first];
        if (newEntity == nullptr) {
            newEntity = new EntityObject(Game::getInstance()->createEntity(), loadedEntity.first);
            entities.push_back(std::unique_ptr<EntityObject>(newEntity));

            instantiatedEntities[loadedEntity.first] = newEntity;
        }

        const auto &component = loadedEntity.second;
        const auto &componentName = component->componentName();

        if (componentFactory->IsPhysicsComponent(componentName)) {
            /** ContactHandler **/
            entitiesPhysicsComponent[newEntity] = component;
        } else {
            auto *newComponent = componentFactory->getComponent(newEntity->GetEntityId(),
                                                                componentName,
                                                                component);
            newEntity->addComponent(newComponent);
        }
    }


    /** Contact Handlers **/
    for (auto &entityPhysicsComponent : entitiesPhysicsComponent) {
        auto *resourceComponent = entityPhysicsComponent.second;
        std::vector<std::string> foundHandlerName{};

        this->getContactHandlerNames(foundHandlerName, *resourceComponent);
        if (foundHandlerName.empty())
            continue;

        auto *entityObject = entityPhysicsComponent.first;

        std::vector<ContactHandler *> contactHandlers{};
        getContactHandlers(contactHandlers, entityObject, foundHandlerName);

        auto *physicsComponent = (PhysicsComponent *) componentFactory->getComponent(entityObject->GetEntityId(),
                                                                                     "PhysicsComponent",
                                                                                     resourceComponent);

        for (ContactHandler *handler : contactHandlers) {
            physicsComponent->contactHandlers.push_back(handler);
        }

        entityObject->addComponent(physicsComponent);
    }
}

void LevelBase::getContactHandlers(std::vector<ContactHandler *> &contactHandlers,
                                   const EntityObject *entityObject,
                                   const std::vector<std::string> &handlerNames) {
    for (const std::string &handlerName : handlerNames) {
        for (auto &entityComponent : entityObject->components) {
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

void LevelBase::getContactHandlerNames(std::vector<std::string> &names,
                                       const Components::component &component) {
    auto &physicsComponent = component.physicsComponent().get();

    for (auto &n : physicsComponent.contactHandler()) {
        names.push_back((string) n.c_str());
    }
}
