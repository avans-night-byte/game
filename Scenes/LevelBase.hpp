#pragma once


#include "../Components/EntityObject.hpp"
#include "../Components/CharacterComponent.hpp"
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

class LevelBase {
private:
    unique_ptr<TMXLevel> tmxLevel;
    std::string levelName;

public:
    CharacterComponent* _characterComponent = nullptr; // TODO: Character data should be stored in global resource file

    void loadEntities(const std::multimap<std::string, Components::component *> &loadedEntities);

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

private:
    void getContactHandlers(std::vector<ContactHandler *> &contactHandlers, EntityObject *entityObject,
                            const std::vector<std::string> &handlerNames);

    void getContactHandlerNames(std::vector<std::string> &names, const Components::component &component);
};