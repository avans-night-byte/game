#include "LevelBase.hpp"

#include "../Components/ComponentFactory.hpp"
#include "../../API/XMLParser/LevelParserAPI.hpp"
#include "../Components/CharacterComponent.hpp"
#include "../Object/ObjectLoader.hpp"


void LevelBase::render() {
    _tmxLevel->render(Game::getInstance()->getRenderingApi());
    for (auto &entity : _entities) {
        entity->render();
    }
}

void LevelBase::update(const Input &inputSystem) {
    for (auto &entity : _entities) {
        entity->update(inputSystem);
    }
}

void LevelBase::fixedUpdate(float deltaTime) {
    for (auto &entity : _entities) {
        entity->fixedUpdate(deltaTime);
    }

}

void LevelBase::initialize(const std::string &name, const LevelData &data) {
    auto outEntities = std::vector<EntityXMLParser::ObjectData>();



    this->_tmxLevel = std::unique_ptr<TMXLevel>(LevelParserAPI::loadLevel(outEntities, data));
    this->_levelName = name;

    ObjectLoader::loadEntities(outEntities, this->_entities);

    this->_entities.push_back(GlobalObjects::getInstance()->loadEntity("MainObjects", "character"));
    this->_entities.push_back(GlobalObjects::getInstance()->loadEntity("MainObjects", "character"));
    this->_entities.push_back(GlobalObjects::getInstance()->loadEntity("MainObjects", "character"));
    this->_entities.push_back(GlobalObjects::getInstance()->loadEntity("MainObjects", "character"));
    this->_entities.push_back(GlobalObjects::getInstance()->loadEntity("MainObjects", "character"));
    this->_entities.push_back(GlobalObjects::getInstance()->loadEntity("MainObjects", "character"));
    this->_entities.push_back(GlobalObjects::getInstance()->loadEntity("MainObjects", "character"));
}

void LevelBase::addObject(const std::string &fromList, const std::string &entityName){
    _entities.push_back(GlobalObjects::getInstance()->loadEntity(fromList, entityName));
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
