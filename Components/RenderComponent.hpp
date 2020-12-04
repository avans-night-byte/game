#pragma once


#include "./Component.hpp"
#include <string>

class EngineRenderingAPI;
class WorldPositionComponent;

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