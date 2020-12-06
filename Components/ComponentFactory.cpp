#include "ComponentFactory.hpp"

#include "WorldPositionComponent.hpp"
#include "CharacterComponent.hpp"
#include "NextLevelComponent.hpp"
#include "RenderComponent.hpp"
#include "EntityObject.hpp"

ComponentFactory::ComponentFactory() {

    Game *game = Game::getInstance();
    EntityId entityId = game->createEntity();


    components["PhysicsComponent"] = make_unique<PhysicsComponent>(entityId);
    components["WorldPositionComponent"] = make_unique<WorldPositionComponent>(entityId);
    components["CharacterComponent"] = make_unique<CharacterComponent>(entityId);
    components["NextLevelComponent"] = make_unique<NextLevelComponent>(entityId);
    components["RenderComponent"] = make_unique<RenderComponent>(entityId);
    components["EntityObject"] = make_unique<EntityObject>(entityId);
}
