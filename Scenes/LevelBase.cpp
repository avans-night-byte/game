#include "LevelBase.hpp"

#include "../Components/EntityObject.hpp"
#include "../Components/ComponentFactory.hpp"
#include "Generated/level-resources.hxx"
#include "../Components/PhysicsComponent.hpp"
#include "../ContactHandlers/ExplosionCrate.hpp"

void LevelBase::LoadEntities(const std::multimap<std::string, const LevelResources::component *> &loadedEntities) {
    auto componentFactory = Game::getInstance()->getComponentFactory();

    auto instantiatedEntities = std::map<std::string, EntityObject *>();
    auto entitiesPhysicsComponent = std::map<EntityObject *, const LevelResources::component *>();

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

        const std::string &foundHandlerName = entityPhysicsComponent.second->physicsComponent()->contactHandler().get();
        if (foundHandlerName.empty())
            continue;

        auto *component = entityPhysicsComponent.second;
        auto *entityObject = entityPhysicsComponent.first;
        Component *foundHandler = nullptr;
        for (auto *entityComponent : entityObject->components) {
            if (entityComponent->name() == foundHandlerName) {
                foundHandler = entityComponent;
                break;
            }
        }

        if (foundHandler == nullptr) {
            throw std::runtime_error("ContactHandler: " + foundHandlerName + " couldn't be found!");
        }
        auto contactHandler = dynamic_cast<ContactHandler *>( foundHandler);
        if (contactHandler == nullptr) {
            throw std::runtime_error(foundHandlerName + " does not derive from ContactHandler");
        }

        auto *physicsComponent = (PhysicsComponent *) componentFactory->getComponent(entityObject->GetEntityId(),
                                                                                     "PhysicsComponent",
                                                                                     component);

        physicsComponent->contactHandlers.push_back(std::unique_ptr<ContactHandler>(contactHandler));
        entityObject->components.push_back(physicsComponent);
    }
}
