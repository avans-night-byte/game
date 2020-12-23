#include "RenderComponent.hpp"
#include "../../Game.hpp"
#include "../PhysicsComponent.hpp"
#include "../TransformComponent.hpp"
#include "Generated/components.hxx"

/**
 * This is a sample component, this one renders an imahe on the screen.
*/

RenderComponent::RenderComponent(EntityId id) : Component(id),
                                                _engineRenderingApi(Game::getInstance()->getRenderingApi()),
                                                _spriteId(),
                                                _texturePath(),
                                                transform(nullptr){

}

std::string RenderComponent::name() const {
    return "RenderComponent";
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
                                 const std::string &spriteId, int width, int height, int offsetX, int offsetY)
        : Component(id),
          _engineRenderingApi(Game::getInstance()->getRenderingApi()),
          _spriteId(spriteId),
          _texturePath(texturePath),
          _width(width),
          _height(height),
          _offsetX(offsetX),
          _offsetY(offsetY) {
    switch (renderType) {
        case TEXTURE: {
            _engineRenderingApi.loadTexture(texturePath, spriteId);
            break;
        }
        case SPRITE_SHEET: {
            _engineRenderingApi.loadSpriteSheet(texturePath, spriteId, width, height);
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
    v2.x -= (float)_width * 0.5f + (float)_offsetX;
    v2.y -= (float)_height * 0.5f + (float)_offsetY;

    if (!_isAnimating) {
        _engineRenderingApi.drawTexture(_spriteId, v2.x, v2.y, _width, _height, 2, transform->rotation);
    } else {
        const auto &currentAnimation = _animation->currentAnimation;
        const auto &animationSpeed = _animation->speed;

        _engineRenderingApi.drawAnimation(_spriteId, v2, currentAnimation, animationSpeed);
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

    auto *newComponent = new RenderComponent(entityId);
    newComponent->_texturePath = resourceComponent->spritePath();
    newComponent->_spriteId = resourceComponent->spriteId();
    newComponent->_width = resourceComponent->width();
    newComponent->_height = resourceComponent->height();


    TextureManager::GetInstance()->load(newComponent->_texturePath,
                                        newComponent->_spriteId);
    return newComponent;
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
