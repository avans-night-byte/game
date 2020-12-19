#pragma once

#include <map>
#include <vector>
#include <string>
#include <stdexcept>

class RenderComponent;

class Animation {
private:
    // pair int = column, int row
    std::map<std::string, std::vector<std::pair<int, int>>> _animation;
    RenderComponent& _renderComponent;

public:
    std::vector<std::pair<int, int>> currentAnimation;

public:
    explicit Animation( RenderComponent& renderComponent);

public:
    void addAnimation(const std::string& name, const std::vector<std::pair<int, int>>& animation);

    void activateAnimation(const std::string& name);
};
