#include "LevelBase.hpp"

#include "../Components/ComponentFactory.hpp"
#include "../../API/XMLParser/LevelParserAPI.hpp"
#include "../Components/CharacterComponent.hpp"
#include "../Object/ObjectLoader.hpp"


void LevelBase::render() {
    _tmxLevel->render(Game::getInstance()->getRenderingApi());
    for (auto &entity : entities) {
        entity->render();
    }

    _characterComponent->render();
}

void LevelBase::update(const Input &inputSystem) {
    _characterComponent->update(inputSystem);
    for (auto &entity : entities) {
        entity->update(inputSystem);
    }
}

void LevelBase::fixedUpdate(float deltaTime) {
    _characterComponent->fixedUpdate(deltaTime);
    for (auto &entity : entities) {
        entity->fixedUpdate(deltaTime);
    }

}

void LevelBase::initialize(const std::string &name, const LevelData &data) {
    auto outEntities = std::multimap<std::string, Components::component *>();

    this->_tmxLevel = std::unique_ptr<TMXLevel>(LevelParserAPI::loadLevel(outEntities, data));
    this->_levelName = name;


    ObjectLoader::loadEntities(outEntities, this->entities);
    std::cout << "KLAAR" << std::endl;
}

void LevelBase::clearEntities() {
    for (auto &entity : entities) {
        for (auto &comp : entity->getComponents()) {
            if (auto *physicsComponent = dynamic_cast<PhysicsComponent *>(comp.get())) {
                physicsComponent->destroyBody();
            }
        }
    }

    _tmxLevel->cleanup();
    entities.clear();
}
