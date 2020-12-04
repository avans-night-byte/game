#pragma once

#include "vector"
#include "../../Components/Component.hpp"

class CharacterComponent;
class Input;



class ExampleScene {
private:
    CharacterComponent& characterComponent;

    // TODO: Make RemoveComponent within Game.
    // TODO: Create function to get all entities;
    std::vector<EntityId> entities{};

    // TODO: Make Entity class with a list of components.
    // TODO: Every Entity has to have WorldComponent.


public:
    explicit ExampleScene(CharacterComponent& characterComponent) : characterComponent(characterComponent)
    {

    }

    ~ExampleScene();

    void initialize();

    void fixedUpdate(const float &deltaTime);

    void update(const Input &inputSystem);
};




