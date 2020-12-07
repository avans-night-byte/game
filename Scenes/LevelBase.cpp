#include "LevelBase.hpp"

#include "../Components/EntityObject.hpp"
#include "../Components/ComponentFactory.hpp"
#include "Generated/level-resources.hxx"

void LevelBase::LoadEntities(const std::multimap<std::string, const LevelResources::component *> &loadedEntities) {
    auto componentFactory = Game::getInstance()->getComponentFactory();

    auto instantiatedEntities = std::map<std::string, EntityObject*>();
    entities = std::vector<std::unique_ptr<EntityObject>>();

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

        newEntity->AddComponent(newComponent);
    }

}
