#include "ComponentFactory.hpp"

#include "TransformComponent.hpp"
#include "Characters/CharacterComponent.hpp"
#include "NextLevelComponent.hpp"
#include "HealthComponent.hpp"
#include "Rendering/RenderComponent.hpp"
#include "EntityObject.hpp"
#include "Characters/ZombieComponent.hpp"

ComponentFactory::ComponentFactory() {

    Game *game = Game::getInstance();
    EntityId entityId = game->createEntity();


    components["PhysicsComponent"] = std::make_unique<PhysicsComponent>(entityId);
    components["RenderComponent"] = std::make_unique<RenderComponent>(entityId);
    components["TransformComponent"] = std::make_unique<TransformComponent>(entityId);
    components["CharacterComponent"] = std::make_unique<CharacterComponent>(entityId);
    components["ZombieComponent"] = std::make_unique<ZombieComponent>(entityId);
    components["NextLevelComponent"] = std::make_unique<NextLevelComponent>(entityId);
    components["HealthComponent"] = std::make_unique<HealthComponent>(entityId);
    components["RenderComponent"] = std::make_unique<RenderComponent>(entityId);
    components["EntityObject"] = std::make_unique<EntityObject>(entityId, EntityObject::EntityType::none);
    components["BulletComponent"] = std::make_unique<BulletComponent>(entityId);
    components["InventoryComponent"] = std::make_unique<InventoryComponent>(entityId);
    components["WeaponComponent"] = std::make_unique<WeaponComponent>(entityId);
    components["BuildComponent"] = std::make_unique<BuildComponent>(entityId);
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
