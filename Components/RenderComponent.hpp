#pragma once
#include "./Component.hpp"
#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "TransformComponent.hpp"

class RenderComponent : Component {
private:
    TransformComponent *transform;
    int r{}, g{}, b{};
    char const * _texturePath;
    EngineRenderingAPI &_engineRenderingApi;
    std::string _textureId;
public:
    void update() override;

    void setColor(int red, int blue, int green);

    void render();

    RenderComponent(EntityId id, TransformComponent *positionComponent, char const *texturePath,
                    std::string textureId, EngineRenderingAPI &engineRenderingApi);
};