#include "LevelBase.hpp"

#include "../Components/ComponentFactory.hpp"
#include "../../API/XMLParser/LevelParserAPI.hpp"
#include "../Components/Characters/CharacterComponent.hpp"
#include "../Object/ObjectLoader.hpp"


void LevelBase::render() {
    _tmxLevel->render(Game::getInstance()->getRenderingApi());
    for (auto &entity : _entities) {
        entity->render();
    }
    this->character->render();
}

void LevelBase::update(const Input &inputSystem) {
    this->character->update(inputSystem);
    for (auto &entity : _entities) {
        entity->update(inputSystem);
    }
}

void LevelBase::fixedUpdate(float deltaTime) {
    this->character->fixedUpdate(deltaTime);
    for (auto &entity : _entities) {
        entity->fixedUpdate(deltaTime);
    }
}

void LevelBase::initialize(const std::string &name, const LevelData &data) {
    auto outEntities = std::vector<EntityXMLParser::ObjectData>();

    this->_tmxLevel = std::unique_ptr<TMXLevel>(LevelParserAPI::loadLevel(outEntities, data));
    this->_levelName = name;

    ObjectLoader::loadEntities(outEntities, this->_entities);

    for (auto wow : outEntities) {
        wow.clearRawData();
    }
}


void LevelBase::clearEntities() {
    for (auto &entity : _entities) {
        for (auto &comp : entity->getComponents()) {
            if (auto *physicsComponent = dynamic_cast<PhysicsComponent *>(comp.get())) {
                physicsComponent->destroyBody();
            }
        }
    }

    _tmxLevel->cleanup();
    _entities.clear();
}

void LevelBase::postInitialize() {

}

TMXLevel& LevelBase::getLevel() {
    return *_tmxLevel;
}
