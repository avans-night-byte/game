#include "RenderComponent.hpp"
#include "../../API/Rendering/EngineRenderingAPI.hpp"


RenderComponent::RenderComponent(EntityId id, WorldPositionComponent *positionComponent, SDL_Renderer *sdlRenderer, char const* texturePath)
: Component(id), position(positionComponent) {
    renderer = sdlRenderer;
    _texturePath = texturePath;


    textureManager = EngineRenderingAPI::GetTextureManager();
    bool textureLoad = textureManager->load(_texturePath, "sample", renderer);

    if(textureLoad){

    }
}

void RenderComponent::setColor(int red, int blue, int green) {
    r = red;
    b = blue;
    g = green;
}
void RenderComponent::render() {
    textureManager->draw("sample", position->x, position->y, 859, 840, 2,0, renderer, SDL_FLIP_NONE);
}

void RenderComponent::update() {
    render();
}