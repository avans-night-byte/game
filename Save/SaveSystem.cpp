
#include "SaveSystem.hpp"
#include "../../Resources/XML/Generated/save.hxx"
#include "../Game.hpp"
#include "../Components/Characters/CharacterComponent.hpp"


void SaveSystem::loadSave(std::string file) {
    auto save = Save::save_(file);

    Game::getInstance()->get
}

