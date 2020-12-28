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

class PlayerSpawnerComponent;

class LevelBase {
private:
    std::unique_ptr<TMXLevel> _tmxLevel{};
    std::string _levelName{};

public:
    EntityObject *character = nullptr;

    LevelBase() = default;


private:
    std::vector<std::unique_ptr<EntityObject>> _entities{};
    std::vector<PlayerSpawnerComponent *> _spawnPoints{};

public:
    template<class T>
    void findComponents(std::vector<T> &foundComponents) {
        static_assert(std::is_base_of<Component, T>::value, "T should inherit from class Component");

        for (auto &comp : _entities) {
            if (auto *found = comp->getComponent<T>()) {
                foundComponents.push_back(found);
            }
        }
    }

    virtual void initialize(const std::string &name, const LevelData &data);

    virtual void postInitialize();

    virtual void render();

    virtual void update(const Input &inputSystem);

    virtual void fixedUpdate(float deltaTime);

    virtual void clearEntities();

    virtual TMXLevel &getLevel();
};