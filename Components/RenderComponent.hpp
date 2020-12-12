#pragma once


#include "./Component.hpp"
#include "TransformComponent.hpp"
#include <string>

class RenderingAPI;
class Spritesheet; // TODO: Remove
class PhysicsComponent;

class WorldPositionComponent;

class RenderComponent : public Component {
private:
    Spritesheet* spriteSheet; // TODO: Remove, store it in the backend in a map.

    TransformComponent *transform;
    PhysicsComponent *physics;

    int r{}, g{}, b{};
    float width;
    float height;
    std::string _texturePath;
    RenderingAPI &_engineRenderingApi;
    std::string _textureId;


public:
    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    void setColor(int red, int blue, int green);

    void render() override;

    explicit RenderComponent(EntityId id);

    RenderComponent(EntityId id, TransformComponent *positionComponent, const std::string &texturePath,
                    std::string textureId);

    [[nodiscard]] std::string name() const override;

    [[nodiscard]] Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

public:

    void setTransform(TransformComponent *pTransform);

    void setPhysicsComponent(PhysicsComponent *pComponent);
};