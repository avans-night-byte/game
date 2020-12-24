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
class BulletComponent;

class LevelBase {
private:
    std::unique_ptr<TMXLevel> _tmxLevel;
    std::string _levelName;

public:
    EntityObject* _character = nullptr; // TODO: Character data should be stored in global resource file

    LevelBase() = default;


private:
    std::vector<std::unique_ptr<EntityObject>> _entities{};

public:
    virtual void initialize(const std::string& name, const LevelData &data);

    virtual void render();

    virtual void update(const Input &inputSystem);

    virtual void fixedUpdate(float deltaTime);

    virtual void clearEntities();

    void addObject(const std::string &fromList, const std::string &entityName);

    virtual TMXLevel& getLevel();
};