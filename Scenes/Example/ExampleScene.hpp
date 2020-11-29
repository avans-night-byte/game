#pragma once

#include "memory"
#include <vector>
#include "../../Components/Component.hpp"
#include "../../Components/CharacterComponent.h"
#include "../../../Engine/Rendering/Spritesheet.hpp"
#include "../../../API/Rendering/EngineRenderingAPI.hpp"
#include "../../Game.hpp"


using namespace std;

class ExampleScene {
private:
    CharacterComponent& characterComponent;

    // TODO: Make RemoveComponent within Game.
    // TODO: Create function to get all entities;
    vector<EntityId> entities{};

    // TODO: Make Entity class with a list of components.
    // TODO: Every Entity has to have WorldComponent.


public:
    explicit ExampleScene(CharacterComponent& characterComponent) : characterComponent(characterComponent)
    {

    }

    ~ExampleScene() {
        Game* game = Game::getInstance();
        for (EntityId id: entities) {
            System<Component> components = game->getComponents(id);

            for (auto component : components.components)
            {
                delete component.second;
            }
        }
    }

    void initialize();

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};




