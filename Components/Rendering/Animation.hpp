#pragma once

#include <map>
#include <vector>
#include <string>
#include <stdexcept>

class RenderComponent;

class Animation {
private:
    // pair int = row, int column
    std::map<std::string, std::vector<std::pair<int, int>>> _animation;
    RenderComponent &_renderComponent;
    std::string _currentAnimationName;

public:
    std::vector<std::pair<int, int>> currentAnimation;
    int speed = 4;

public:
    explicit Animation(RenderComponent &renderComponent);

public:
    void addAnimation(const std::string &name,
                      const std::vector<std::pair<int, int>> &animation);

    void activateAnimation(const std::string &name);

};
