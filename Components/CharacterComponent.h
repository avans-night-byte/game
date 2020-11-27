#pragma once


#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "Component.hpp"
#include "../Game.hpp"
#include "WorldPositionComponent.hpp"

class CharacterComponent : public Component {
private:
    Spritesheet *spriteSheet;
    unique_ptr<WorldPositionComponent> worldPosition;

public:
    explicit CharacterComponent(EntityId id,
                                const EngineRenderingAPI *renderingApi,
                                const Vector2 &position) : Component(id) {
        spriteSheet = renderingApi->createSpriteSheet("../../Resources/Sprites/character.png",
                                                      "spritesheet_char", 8, 11, 100, 105);

        worldPosition = make_unique<WorldPositionComponent>(id);
        worldPosition->setLocation(position.x, position.y);


        Game *game = Game::getInstance();
        game->addComponent(id, worldPosition.get());


        spriteSheet->select_sprite(0, 0);
    }

    void update() override {


        spriteSheet->draw_selected_sprite(worldPosition->x, worldPosition->y);
    }

    inline const Spritesheet &getSpriteSheet() {
        return *spriteSheet;
    }
};

