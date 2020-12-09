#include "RenderComponent.hpp"
#include "../Game.hpp"
#include "WorldPositionComponent.hpp"
#include "../../API/Rendering/RenderingAPI.hpp"

/**
 * This is a sample component, this one renders an imahe on the screen.
*/

RenderComponent::RenderComponent(EntityId id) : Component(id),
                                                _engineRenderingApi(*Game::getInstance()->getRenderingApi()),
                                                _textureId(),
                                                _texturePath(),
                                                position(nullptr) {

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
RenderComponent::RenderComponent(EntityId id, WorldPositionComponent *positionComponent, char const *texturePath,
                                 std::string textureId)
        : Component(id),
          position(positionComponent),
          _engineRenderingApi(*Game::getInstance()->getRenderingApi()),
          _textureId(std::move(textureId)) {

    _texturePath = texturePath;
    _engineRenderingApi.loadTexture(texturePath, "");
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
 *  Sample rendering function, the components are pretty much a poc.
 */
void RenderComponent::render() {
    //Render the texture
    _engineRenderingApi.drawTexture(_textureId, *position->physicsX, *position->physicsY, 859, 840, 2, 0);
}


void RenderComponent::fixedUpdate(const float &deltaTime) {

}

Component *RenderComponent::clone(EntityId entityId, const Components::component *component) {
    return new RenderComponent(entityId);
}

void RenderComponent::update(const Input &inputSystem) {

}
