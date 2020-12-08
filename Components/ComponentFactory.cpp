#include "ComponentFactory.hpp"

#include "WorldPositionComponent.hpp"
#include "CharacterComponent.hpp"
#include "NextLevelComponent.hpp"
#include "RenderComponent.hpp"
#include "EntityObject.hpp"
#include "../ContactHandlers/ExplosionCrate.hpp"

ComponentFactory::ComponentFactory() {

    Game *game = Game::getInstance();
    EntityId entityId = game->createEntity();


    components["PhysicsComponent"] = make_unique<PhysicsComponent>(entityId);
    components["WorldPositionComponent"] = make_unique<WorldPositionComponent>(entityId);
    components["CharacterComponent"] = make_unique<CharacterComponent>(entityId);
    components["NextLevelComponent"] = make_unique<NextLevelComponent>(entityId);
    components["RenderComponent"] = make_unique<RenderComponent>(entityId);
    components["EntityObject"] = make_unique<EntityObject>(entityId);
//    components["ExplosionCrate"] = make_unique<ExplosionCrate>(entityId);
}

Component *ComponentFactory::getComponent(const EntityId &id,
                                          const string &name,
                                          const LevelResources::component *loadedComponent) {

    std::unique_ptr<Component> &component = components[name];

    if (component == nullptr) {
        std::cout << "Couldn't find " + name + ", will create EntityObject component." << std::endl;
        return components["EntityObject"]->clone(id, nullptr);
    }

    return component->clone(id, loadedComponent);
}
