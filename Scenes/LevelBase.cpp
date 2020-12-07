#include "LevelBase.hpp"

#include "../Components/EntityObject.hpp"
#include "../Components/ComponentFactory.hpp"
#include "Generated/level-resources.hxx"
#include "../Components/PhysicsComponent.hpp"

void LevelBase::LoadEntities(const std::multimap<std::string, const LevelResources::component *> &loadedEntities) {
    auto componentFactory = Game::getInstance()->getComponentFactory();
    entities = std::vector<std::unique_ptr<EntityObject>>();

    auto instantiatedEntities = std::map<std::string, EntityObject *>();
    auto entitiesPhysicsComponent = std::map<EntityObject *, PhysicsComponent *>();

    for (auto &loadedEntity : loadedEntities) {
        auto &newEntity = instantiatedEntities[loadedEntity.first];
        if (newEntity == nullptr) {
            newEntity = new EntityObject(Game::getInstance()->createEntity(), loadedEntity.first);
            entities.push_back(std::unique_ptr<EntityObject>(newEntity));

            instantiatedEntities[loadedEntity.first] = newEntity;
        }

        const auto loadedComponent = loadedEntity.second;
        auto *newComponent = componentFactory->getComponent(newEntity->GetEntityId(),
                                                            loadedEntity.second->componentName(),
                                                            loadedComponent);

        /** ContactHandler **/
        auto *physicsComponent = (PhysicsComponent *) newComponent;
        if (physicsComponent != nullptr) {
            entitiesPhysicsComponent[newEntity] = physicsComponent;
        }

        newEntity->AddComponent(newComponent);
    }


    /** Contact Handlers **/
    for (auto &entityPhysicsComponent : entitiesPhysicsComponent) {
        const std::string &foundHandlerName = entityPhysicsComponent.second->getContactHandlerName();
        if (foundHandlerName.empty())
            continue;

        bool contactHandlerInitialized = false;
        for (auto &component : entityPhysicsComponent.first->getComponents()) {
            if (component->name() == foundHandlerName) {

                auto *contactHandler = (ContactHandler *) component.get();
                if (contactHandler == nullptr)
                    throw std::runtime_error(component->name() + " does not inherit ContactHandler");

                entityPhysicsComponent.second->setContactHandler(component.get());

                contactHandlerInitialized = true;
                break;
            }
        }

        if (!contactHandlerInitialized) {
            throw std::runtime_error("ContactHandler: " + foundHandlerName + " couldn't be found!");
        }
    }
}
