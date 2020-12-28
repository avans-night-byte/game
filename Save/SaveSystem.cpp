
#include "SaveSystem.hpp"
#include "../../Resources/XML/Generated/save.hxx"
#include "../Game.hpp"
#include "../Components/Characters/CharacterComponent.hpp"


void SaveSystem::loadSave(const std::string& file) {
    auto save = Save::save_(file);

    Game::getInstance()->getCharacter()->getComponent<PhysicsComponent>()->setTransform(Vector2(300, 300), 0);
}

