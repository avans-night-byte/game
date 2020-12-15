#include "LevelBase.hpp"

#include "../Components/ComponentFactory.hpp"
#include "../../API/XMLParser/LevelParserAPI.hpp"
#include "../Components/CharacterComponent.hpp"
#include "../Object/ObjectLoader.hpp"
#include "../Object/GlobalObjects.hpp"


void LevelBase::render() {
    tmxLevel->render(Game::getInstance()->getRenderingApi());
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

    this->tmxLevel = std::unique_ptr<TMXLevel>(LevelParserAPI::loadLevel(outEntities, data));
    this->levelName = name;


    ObjectLoader::loadEntities(outEntities, this->entities);
    ResourceManager::getInstance()->loadResource("MainObjects");
    auto bullet = GlobalObjects::getInstance()->getLoadedEntity("MainObjects", "bullet1", 1000);


    // TODO: Remove
    _characterComponent->initializeWeapons(entities);
}

void LevelBase::destroyAllBodies() {
    for (auto &entity : entities) {
        for (auto &comp : entity->getComponents()) {
            if (auto *physicsComponent = dynamic_cast<PhysicsComponent *>(comp.get())) {
                physicsComponent->destroyBody();
            }
        }
    }

    tmxLevel->cleanup();
}

void LevelBase::clearEntities() {
    entities.clear();
}