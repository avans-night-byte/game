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
                                                _textureId(),
                                                _texturePath(),
                                                transform(nullptr) {

}

std::string RenderComponent::name() const {
    return "RenderComponent";
}

/**
 * Instantiates the rendering and passes any needed variables like the engineRenderingApi
 * @param id
 * @param transform
 * @param texturePath
 * @param textureId
 * @param engineRenderingApi
 */
RenderComponent::RenderComponent(EntityId id, RenderType renderType, const std::string &texturePath,
                                 const std::string &textureId, int width, int height)
        : Component(id),
          _engineRenderingApi(Game::getInstance()->getRenderingApi()),
          _textureId(textureId),
          _texturePath(texturePath),
          _renderType(renderType),
          _width(width),
          _height(height) {
    switch (renderType) {
        case TEXTURE: {
            _engineRenderingApi.loadTexture(texturePath, textureId);
            break;
        }
        case SPRITE_SHEET: {
            _engineRenderingApi.loadSpriteSheet(texturePath, textureId, width, height);
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
    if (!_isAnimating) {
        Vector2 v2 = transform->getPosition();
        _engineRenderingApi.drawTexture(_textureId, v2.x - (_width * 0.5f),
                                        v2.y - (_height * 0.5f), _width, _height, 2, transform->rotation);
    } else {
         _animation->currentAnimation;
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
    newComponent->_textureId = resourceComponent->spriteId();
    newComponent->_width = resourceComponent->width();
    newComponent->_height = resourceComponent->height();


    TextureManager::GetInstance()->load(newComponent->_texturePath,
                                        newComponent->_textureId);
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
