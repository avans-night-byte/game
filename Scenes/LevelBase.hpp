#pragma once


#include "../Components/EntityObject.hpp"

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
public:
    void LoadEntities(const std::multimap<std::string, const Components::component *> &loadedEntities);

protected:
    std::vector<std::unique_ptr<EntityObject>> entities{};

public:
    virtual void render() = 0;

    virtual void update(const Input &inputSystem) = 0;

    virtual void fixedUpdate(const float &deltaTime) = 0;

private:
    void getContactHandlers(std::vector<ContactHandler *> &contactHandlers, const EntityObject *entityObject,
                            const std::vector<std::string> &handlerNames);

    void getContactHandlerNames(std::vector<std::string> &names,
                                const Components::component &component);
};