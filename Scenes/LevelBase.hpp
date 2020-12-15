#pragma once


#include "../Components/EntityObject.hpp"
#include "../../Engine/Rendering/TMXLevel.hpp"


#include <string>
#include <map>
#include <vector>
#include <memory>


namespace Components {
    class component;
}
class Input;
class ContactHandler;
class CharacterComponent;
class LevelData;

class LevelBase {
private:
    std::unique_ptr<TMXLevel> tmxLevel;
    std::string levelName;

public:
    CharacterComponent* _characterComponent = nullptr; // TODO: Character data should be stored in global resource file

    LevelBase() = default;

    void initialize(const std::string& name, const LevelData &data);

protected:
    std::vector<std::unique_ptr<EntityObject>> entities{};

public:
    void render();

    void update(const Input &inputSystem);

    void fixedUpdate(float deltaTime);

    void destroyAllBodies();

    void clearEntities();
};