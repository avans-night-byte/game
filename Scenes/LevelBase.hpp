#pragma once


#include "../Components/EntityObject.hpp"

#include <string>
#include <map>
#include <vector>
#include <memory>


namespace LevelResources {
    class component;
}
class Input;

class LevelBase {
public:
    void LoadEntities(const std::multimap<std::string, const LevelResources::component *>& loadedEntities);

protected:
    std::vector<std::unique_ptr<EntityObject>> entities{};

public:
    virtual void render() = 0;

    virtual void update(const Input &inputSystem) = 0;

    virtual void fixedUpdate(const float &deltaTime) = 0;
};