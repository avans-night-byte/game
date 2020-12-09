#pragma once


#include "./Component.hpp"
#include <string>

class RenderingAPI;
class WorldPositionComponent;

class RenderComponent : public Component {
private:
    WorldPositionComponent *position;
    int r{}, g{}, b{};
    char const * _texturePath;
    RenderingAPI &_engineRenderingApi;
    std::string _textureId;


public:
    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    void setColor(int red, int blue, int green);

    void render();

    explicit RenderComponent(EntityId id);

    RenderComponent(EntityId id, WorldPositionComponent *positionComponent, char const *texturePath,
                    std::string textureId);

    [[nodiscard]] std::string name() const override;

    [[nodiscard]] Component *clone(EntityId entityId, const Components::component *component) override;
};