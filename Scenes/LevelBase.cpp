#include "LevelBase.hpp"

#include "../Components/ComponentFactory.hpp"
#include "../Components/Characters/CharacterComponent.hpp"
#include "../Object/ObjectLoader.hpp"


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
    auto outEntities = std::vector<EntityXMLParser::ObjectData>();

    this->_tmxLevel = std::unique_ptr<TMXLevel>(LevelParserAPI::loadLevel(outEntities, data));
    this->_levelName = name;

    ObjectLoader::loadEntities(outEntities, this->_entities);
    for (int i = 0; i < 20; ++i) {
        auto &entityObject = Game::getInstance()->getPoolLevel()->getPool("zombie").getEntity();
        entityObject.getComponent<PhysicsComponent>()->setEnabled(true);
        entityObject.getComponent<PhysicsComponent>()->setTransform(Vector2(500.f - (i * 5),
                                                                            500.f + (i * 5)), 0);
    }

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
