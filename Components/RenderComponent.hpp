#pragma once
#include <SDL_render.h>
#include "./Component.hpp"
#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "WorldPositionComponent.hpp"

class RenderComponent : Component {
private:
    WorldPositionComponent *position;
    int r{}, g{}, b{};
    char const * _texturePath;
    EngineRenderingAPI &_engineRenderingApi;
    std::string _textureId;
public:
    void update() override;

    void setColor(int red, int blue, int green);

    void render();

    RenderComponent(EntityId id, WorldPositionComponent *positionComponent, char const *texturePath,
                    std::string textureId, EngineRenderingAPI &engineRenderingApi);
};