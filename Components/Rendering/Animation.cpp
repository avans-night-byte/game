#include "Animation.hpp"

#include "RenderComponent.hpp"

Animation::Animation(RenderComponent &renderComponent) : _renderComponent(renderComponent) {

}

void Animation::addAnimation(const std::string &name, const std::vector<std::pair<int, int>> &animation) {
    auto it = _animation.insert(std::pair(name, animation));
    if (!it.second)
        throw std::runtime_error("An animation of the current RenderComponent already exists. RenderComponent ID=" +
                                 std::to_string(_renderComponent.getEntityId()));
}

void Animation::activateAnimation(const std::string &name) {
    auto it = _animation.find(name);
    if (it == _animation.end())
        throw std::runtime_error("Animation '" + name + "' DOES NOT EXISTS");

    currentAnimation = it->second;

    _renderComponent.isAnimating();
}
