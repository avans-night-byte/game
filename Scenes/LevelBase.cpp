#include "LevelBase.hpp"

#include "../Components/ComponentFactory.hpp"
#include "../../API/XMLParser/LevelParserAPI.hpp"

#include "Generated/level-resources.hxx"

void LevelBase::loadEntities(const std::multimap<std::string, Components::component *> &loadedEntities) {
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

        if (componentFactory->IsPhysicsComponent(componentName)) {
            /** ContactHandler **/
            entitiesPhysicsComponent[newEntity] = component;
        } else {
            auto *newComponent = componentFactory->getComponent(newEntity->getEntityId(),
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
        auto *worldPositionComponent = setPositionForComponent(entityObject, resourceComponent);
        auto *physicsComponent = (PhysicsComponent *) componentFactory->getComponent(entityObject->getEntityId(),
                                                                                     "PhysicsComponent",
                                                                                     resourceComponent);

        for (ContactHandler *handler : contactHandlers) {
            physicsComponent->contactHandlers.push_back(handler);
        }

        if (worldPositionComponent) {
            const RPosition &rPosition = physicsComponent->getRPosition();
            worldPositionComponent->refLocation(rPosition.X, rPosition.Y);
        }

        entityObject->addComponent(physicsComponent);
    }


    for(auto &entity : entities) {
        entity->initializeComponents();
    }
}

void LevelBase::getContactHandlers(std::vector<ContactHandler *> &contactHandlers,
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

void LevelBase::getContactHandlerNames(std::vector<std::string> &names,
                                       const Components::component &component) {
    auto &physicsComponent = component.physicsComponent().get();

    for (auto &n : physicsComponent.contactHandler()) {
        names.push_back((string) n.c_str());
    }
}


void LevelBase::render() {
    tmxLevel->render(Game::getInstance()->getRenderingApi());
    for (auto &entity : entities) {
        entity->render();
    }
    characterComponent->render();
}

void LevelBase::update(const Input &inputSystem) {
    characterComponent->update(inputSystem);
    for (auto &entity : entities) {
        entity->update(inputSystem);
    }
}

void LevelBase::fixedUpdate(const float &deltaTime) {
    characterComponent->fixedUpdate(deltaTime);
    for (auto &entity : entities) {
        entity->fixedUpdate(deltaTime);
    }
}

void LevelBase::initialize(const std::string &name, const LevelData &data) {
    auto outEntities = std::multimap<std::string, Components::component *>();
    auto *tmx = LevelParserAPI::loadLevel(outEntities, data);

    this->tmxLevel = std::unique_ptr<TMXLevel>(tmx);
    this->loadEntities(outEntities);
    this->levelName = name;
}

TransformComponent *LevelBase::setPositionForComponent(EntityObject *pObject, Components::component *component) {
    for (auto &c : pObject->getComponents()) {
        auto *worldPositionComponent = dynamic_cast<TransformComponent *>(c.get());
        if (worldPositionComponent != nullptr) {
            auto &pPhysicsComponent = component->physicsComponent().get();
            pPhysicsComponent.position().x() = float(*worldPositionComponent->physicsX);
            pPhysicsComponent.position().y() = float(*worldPositionComponent->physicsY);
            return worldPositionComponent;
        }
    }

    return nullptr;
}

void LevelBase::destroyAllBodies() {
    for (auto &entity : entities) {
        for (auto &comp : entity->getComponents()) {
            if (auto *physicsComponent = dynamic_cast<PhysicsComponent *>(comp.get())) {
                physicsComponent->destroyBody();
            }
        }
    }

    tmxLevel->cleanup();
}

void LevelBase::clearEntities() {
    entities.clear();
}