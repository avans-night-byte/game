#include "RenderComponent.hpp"
#include "../Game.hpp"
#include "PhysicsComponent.hpp"
#include "TransformComponent.hpp"
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
 * @param positionComponent
 * @param texturePath
 * @param textureId
 * @param engineRenderingApi
 */
RenderComponent::RenderComponent(EntityId id, TransformComponent *positionComponent, const std::string &texturePath,
                                 std::string textureId)
        : Component(id),
          transform(positionComponent),
          _engineRenderingApi(Game::getInstance()->getRenderingApi()),
          _textureId(std::move(textureId)) {

    _texturePath = texturePath;
    _engineRenderingApi.loadTexture(texturePath.c_str(), textureId);
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
    _engineRenderingApi.drawTexture(_textureId, *transform->physicsX - (width * 0.5f),
                                    *transform->physicsY - (height * 0.5f), width, height, 2, transform->rotation);
}


void RenderComponent::fixedUpdate(const float &deltaTime) {
    if (physics != nullptr) {
        const RTransform &rPosition = physics->getRTransform();
        transform->setRotation(rPosition.rotation);
    }
}

Component *RenderComponent::clone(EntityId entityId, const Components::component *component) {
    const auto &resourceComponent = component->renderComponent();

    auto *newComponent = new RenderComponent(entityId);
    newComponent->_texturePath = resourceComponent->spritePath();
    newComponent->_textureId = resourceComponent->spriteId();
    newComponent->width = resourceComponent->width();
    newComponent->height = resourceComponent->height();


    TextureManager::GetInstance()->load(newComponent->_texturePath.c_str(),
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