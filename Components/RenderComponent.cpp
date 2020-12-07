#include "RenderComponent.hpp"
/**
 * This is a sample component, this one renders an imahe on the screen.
*/


/**
 * Instantiates the rendering and passes any needed variables like the engineRenderingApi
 * @param id
 * @param positionComponent
 * @param texturePath
 * @param textureId
 * @param engineRenderingApi
 */
RenderComponent::RenderComponent(EntityId id, TransformComponent *positionComponent, char const *texturePath,
                                 std::string textureId, EngineRenderingAPI &engineRenderingApi)
        : Component(id), transform(positionComponent), _engineRenderingApi(engineRenderingApi), _textureId(std::move(textureId)) {
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
    _engineRenderingApi.drawTexture(_textureId, *transform->x, *transform->y, 859, 840, 2, transform->rotation);
}


/**
 * Update calls the "render function", this is needed to call update no mather what type it is.
 */
void RenderComponent::update() {
    render();
}