#include "RenderComponent.hpp"

#include "../../Game.hpp"
#include "../TransformComponent.hpp"
#include "Generated/components.hxx"

RenderComponent::RenderComponent(EntityId id) : Component(id),
                                                _engineRenderingApi(Game::getInstance()->getRenderingAPI()),
                                                _spriteId(),
                                                _texturePath(),
                                                transform(nullptr) {
}


std::string RenderComponent::name() const {
    return "RenderComponent";
}

/**
 * Reuse a sprite sheet id.
*/

RenderComponent::RenderComponent(EntityId id,
                                 std::string spriteId,
                                 const Vector2 &size,
                                 const Vector2 &offset)
        : Component(id),
          _engineRenderingApi(Game::getInstance()->getRenderingAPI()),
          _spriteId(std::move(spriteId)),
          _size(size),
          _offset(offset){

}

/**
 * Instantiates the rendering and passes any needed variables like the engineRenderingApi
 * @param id
 * @param transform
 * @param texturePath
 * @param spriteId
 * @param engineRenderingApi
 */
RenderComponent::RenderComponent(EntityId id, RenderType renderType, const std::string &texturePath,
                                 const std::string &spriteId, const Vector2 &size, const Vector2 &offset)
        : Component(id),
          _engineRenderingApi(Game::getInstance()->getRenderingAPI()),
          _spriteId(spriteId),
          _texturePath(texturePath),
          _size(size),
          _offset(offset) {
    switch (renderType) {
        case TEXTURE: {
            _engineRenderingApi.loadTexture(texturePath, spriteId);
            break;
        }
        case SPRITE_SHEET: {
            _engineRenderingApi.loadSpriteSheet(texturePath, spriteId, size.x, size.y, offset.x, offset.y);
            break;
        }
    }
}

/**
 * @param red
 * @param blue
 * @param green
 */
void RenderComponent::setColor(int red, int blue, int green) {
    r = red;
    b = blue;
    g = green;
}

/**
 *  Sample rendering function, the _components are pretty much a poc.
 */
void RenderComponent::render() {
    //Render the texture
    Vector2 v2 = transform->getPosition();
    v2.x -= (float) _size.x * 0.5f + (float)_offset.x;
    v2.y -= (float) _size.y * 0.5f + (float)_offset.y;

    if (!_isAnimating) {
        _engineRenderingApi.drawTexture(_spriteId, v2.x, v2.y, _size.x, _size.y, 2, transform->rotation);
    } else {
        const auto &currentAnimation = _animation->currentAnimation;
        const auto &animationSpeed = _animation->speed;

        _engineRenderingApi.drawAnimation(_spriteId, v2, _size, animationSpeed, currentAnimation);
    }
}


void RenderComponent::fixedUpdate(const float &deltaTime) {
    if (physics != nullptr) {
        const RTransform &rPosition = physics->getRTransform();
        transform->setRotation(rPosition.rotation);
    }
}

Component *RenderComponent::build(EntityId entityId, const Components::component *component) {
    const auto &resourceComponent = component->renderComponent();

    Vector2 size{resourceComponent->size().width(), resourceComponent->size().height()};
    Vector2 offset{resourceComponent->offset().width(), resourceComponent->offset().height()};

    if (!resourceComponent->spritePath().present()) {
        auto *newComponent = new RenderComponent(entityId,
                                                 resourceComponent->spriteId(),
                                                 size,
                                                 offset);
        return newComponent;
    }


    return new RenderComponent(entityId,
                               RenderType::TEXTURE,
                               resourceComponent->spritePath().get(),
                               resourceComponent->spriteId(),
                               size,
                               offset);
}

void RenderComponent::update(const Input &inputSystem) {

}

void RenderComponent::initialize(EntityObject &entityParent) {
    if (auto *transformComponent = entityParent.getComponent<TransformComponent>()) {
        transform = transformComponent;
    }

    if (auto *physicsComponent = entityParent.getComponent<PhysicsComponent>()) {
        physics = physicsComponent;
    }
}

void RenderComponent::setAnimation(Animation *animation) {
    _animation = std::unique_ptr<Animation>(animation);
}

void RenderComponent::isAnimating() {
    _isAnimating = true;
}

std::string &RenderComponent::getSpriteID() {
    return _spriteId;
}
