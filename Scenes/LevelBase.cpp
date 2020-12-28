#include "LevelBase.hpp"

#include "../Components/ComponentFactory.hpp"
#include "../Components/Characters/CharacterComponent.hpp"
#include "../Object/ObjectLoader.hpp"
#include "../Components/PlayerSpawnerComponent.hpp"


void LevelBase::render() {
    _tmxLevel->render(Game::getInstance()->getRenderingAPI());
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
    Game *game = Game::getInstance();
    auto outEntities = std::vector<EntityXMLParser::ObjectData>();

    this->_tmxLevel = std::unique_ptr<TMXLevel>(LevelParserAPI::loadLevel(outEntities, data));
    this->_levelName = name;

    ObjectLoader::loadEntities(outEntities, this->_entities);

    for (auto &entity : _entities) {
        if (entity->getComponent<PlayerSpawnerComponent>()) {
            _spawnPoints.push_back(entity->getComponent<PlayerSpawnerComponent>());
        }
    }

    if (game->currentSpawner) {
        for (auto &point : _spawnPoints) {
            if (game->currentSpawner->getPointName() == point->getPointName()) {
                character->getPhysicsComponent()->setTransform(point->getTransformComponent()->getPosition(),
                                                               0.0f);
            }
        }
        game->currentSpawner = nullptr;
    }

    for (auto d : outEntities) {
        d.clearRawData();
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

TMXLevel &LevelBase::getLevel() {
    return *_tmxLevel;
}