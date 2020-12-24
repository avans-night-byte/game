#pragma once

#include "../Component.hpp"
#include "Animation.hpp"
#include "../../../API/Helpers/Vector2.hpp"
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


    explicit RenderComponent(EntityId id);

    RenderComponent(EntityId id,
                    std::string spriteId,
                    const Vector2 &size,
                    const Vector2 &offset);

    /* Creates a new SpriteSheet */
    RenderComponent(EntityId id, RenderType renderType, const std::string &texturePath,
                    const std::string &spriteId, const Vector2 &size, const Vector2 &offset);

private:
    RenderingAPI &_engineRenderingApi;

    TransformComponent *transform = nullptr;
    PhysicsComponent *physics = nullptr;

    int r{}, g{}, b{};
    Vector2 _size{};
    Vector2 _offset{};

    std::string _texturePath {};
    std::string _spriteId {};
    std::unique_ptr<Animation> _animation {};

    bool _isAnimating = false;

public:
    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    void setColor(int red, int blue, int green);

    void render() override;


    [[nodiscard]] std::string name() const override;

    [[nodiscard]] Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    [[nodiscard]] Animation *getAnimation() {
        return _animation.get();
    }

    void setAnimation(Animation *animation);

    void isAnimating();

    std::string &getSpriteID();
};