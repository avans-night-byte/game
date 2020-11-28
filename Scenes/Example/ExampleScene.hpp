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
    EntityId characterEntityId;
    unique_ptr<CharacterComponent> characterComponent;

    vector<Spritesheet> sprites{};

    // TODO: Make Entity class with a list of components.
    // TODO: Every Entity has to have WorldComponent.

public:
    explicit ExampleScene(const EngineRenderingAPI *renderingApi) {
        Game *game = Game::getInstance();
        characterEntityId = game->createEntity();
        characterComponent = make_unique<CharacterComponent>(characterEntityId, renderingApi, Vector2(100, 100));

        game->addComponent(characterEntityId, characterComponent.get());
        sprites.push_back(characterComponent->getSpriteSheet());
    }

    void initialize();

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};




