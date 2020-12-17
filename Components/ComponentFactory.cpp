#include "ComponentFactory.hpp"

#include "TransformComponent.hpp"
#include "CharacterComponent.hpp"
#include "NextLevelComponent.hpp"
#include "RenderComponent.hpp"
#include "EntityObject.hpp"
#include "../ContactHandlers/ExplosionCrate.hpp"

ComponentFactory::ComponentFactory() {

    Game *game = Game::getInstance();
    EntityId entityId = game->createEntity();


    components["PhysicsComponent"] = std::make_unique<PhysicsComponent>(entityId);
    components["RenderComponent"] = std::make_unique<RenderComponent>(entityId);
    components["TransformComponent"] = std::make_unique<TransformComponent>(entityId);
    components["CharacterComponent"] = std::make_unique<CharacterComponent>(entityId);
    components["NextLevelComponent"] = std::make_unique<NextLevelComponent>(entityId);
    components["RenderComponent"] = std::make_unique<RenderComponent>(entityId);
    components["EntityObject"] = std::make_unique<EntityObject>(entityId);
    components["ExplosionCrate"] = std::make_unique<ExplosionCrate>(entityId);
    components["BulletComponent"] = std::make_unique<BulletComponent>(entityId);
}

Component *ComponentFactory::getComponent(const EntityId &id,
                                          const std::string &name,
                                          const Components::component *loadedComponent) {

    std::unique_ptr<Component> &component = components[name];

    if (component == nullptr) {
        std::cout << "Couldn't find " + name + ", will create EntityObject component." << std::endl;
        return components["EntityObject"]->build(id, nullptr);
    }

    return component->build(id, loadedComponent);
}
