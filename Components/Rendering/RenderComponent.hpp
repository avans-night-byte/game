#pragma once


#include "../Component.hpp"
#include "Animation.hpp"
#include <string>

class RenderingAPI;

class SpriteSheet; // TODO: Remove
class PhysicsComponent;

class TransformComponent;

class RenderComponent : public Component {
public:
    enum RenderType {
        TEXTURE,
        SPRITE_SHEET
    };

private:
    RenderingAPI &_engineRenderingApi;

    TransformComponent *transform = nullptr;
    PhysicsComponent *physics = nullptr;

    int r{}, g{}, b{};
    int _width;
    int _height;
    RenderType _renderType;
    std::string _texturePath;
    std::string _textureId;
    std::unique_ptr<Animation> _animation;

    bool _isAnimating = false;

public:
    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    void setColor(int red, int blue, int green);

    void render() override;

    explicit RenderComponent(EntityId id);

    RenderComponent(EntityId id, RenderType renderType, const std::string &texturePath,
                    const std::string &textureId, int width, int height);

    [[nodiscard]] std::string name() const override;

    [[nodiscard]] Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void setAnimation(Animation *animation);

    void isAnimating();
};