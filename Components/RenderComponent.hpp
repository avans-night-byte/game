#pragma once

#include <SDL_render.h>
#include "./Component.hpp"
#include "../../Engine/Rendering/TextureManager.hpp"
#include "WorldPositionComponent.hpp"


class RenderComponent : Component {
    private:
        SDL_Renderer * renderer;
        WorldPositionComponent * position;
        SDL_Texture * model;
        int r,g,b;
        char const* _texturePath;
        TextureManager* textureManager;

    public:
        void update() override;
        void setColor(int red, int blue, int green);
        void render();
        RenderComponent(EntityId id, WorldPositionComponent *positionComponent, SDL_Renderer *sdlRenderer, char const* texturePath);
};


