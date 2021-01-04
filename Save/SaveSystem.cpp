
#include <fstream>
#include "SaveSystem.hpp"
#include "../../Resources/XML/Generated/save.hxx"
#include "../Game.hpp"
#include "../Components/Characters/CharacterComponent.hpp"
#include <filesystem>

void SaveSystem::loadSave(const std::string &file) {
    auto save = Save::save_(file);
    auto game = Game::getInstance();

    game->getCharacter()->getComponent<PhysicsComponent>()->setTransform(
            Vector2(save->playerData().position().x(), save->playerData().position().y()), 0);

    game->getCharacter()->getComponent<WalletComponent>()->setZombytes(save->playerData().money());
    game->getCharacter()->getComponent<HealthComponent>()->setHealth(save->playerData().health());

    for (Save::item item : save->inventoryData().item()) {
        EntityObject::EntityType type;

        if (item.type() == "weapon") {
            type = EntityObject::EntityType::weapon;
        } else if (item.type() == "resource") {
            type = EntityObject::EntityType::resource;
        } else if (item.type() == "object") {
            type = EntityObject::EntityType::object;
        }

        game->getCharacter()->getComponent<InventoryComponent>()->addToInventory(
                new InventoryItem{item.quantity(), item.name(), type});
    }

    ResourceManager::getInstance()->loadResource(save->playerData().level());
    SaveSystem::loadPoolData(file, save->playerData().level());

}

void SaveSystem::loadPoolData(const std::string &file, const std::string &level) {
    if (std::filesystem::exists("../../Resources/Saves/save.xml")) {

        auto save = Save::save_(file);
        auto game = Game::getInstance();

        for (auto object : save->objectData().object()) {
            if (object.level() != level) continue;

            EntityObject &placeable = game->getPoolLevel()->getPool(object.type()).getEntity();

            PhysicsComponent *physicsComponent = placeable.getPhysicsComponent();
            Game::getInstance()->addEventBodyHandler([physicsComponent] { physicsComponent->setEnabled(true); });

            physicsComponent->setTransform(Vector2(object.position().x(), object.position().y()), false);
        }
    }
}

void SaveSystem::saveSave(const std::string &file, const std::string &level) {

    auto game = Game::getInstance();


    std::string xml = "";

    // HEADER
    xml.append("<?xml version=\"1.1\" encoding=\"UTF-8\"?>\n");
    xml.append("<sv:save\n");
    xml.append("        xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n");
    xml.append("        xsi:schemaLocation=\"Save  ../XML/Schemas/save.xsd\n");
    xml.append("                            Common ../XML/Schemas/common.xsd\"\n");
    xml.append("        xmlns:common=\"Common\"\n");
    xml.append("        xmlns:sv=\"Save\">\n");

    // PLAYER DATA
    xml.append("    <playerData>\n");
    xml.append("        <common:position>\n");
    xml.append("            <x>" + std::to_string(game->getCharacter()->getTransform()->getPosition().x) + "</x>\n");
    xml.append("            <y>" + std::to_string(game->getCharacter()->getTransform()->getPosition().y) + "</y>\n");
    xml.append("        </common:position>\n");
    xml.append("        <health>" + std::to_string(game->getCharacter()->getComponent<HealthComponent>()->getHealth()) +
               "</health>\n");
    xml.append(
            "        <money>" + std::to_string(game->getCharacter()->getComponent<WalletComponent>()->getZombytes()) +
            "</money>\n");
    xml.append("        <level>" + level + "</level>\n");
    xml.append("    </playerData>\n");

    // INVENTORY DATA
    xml.append("    <inventoryData>\n");
    for (InventoryItem *item : game->getCharacter()->getComponent<InventoryComponent>()->getInventoryItems()) {
        xml.append("        <item>\n");
        xml.append("            <name>" + item->getName() + "</name>\n");
        xml.append("            <quantity>" + std::to_string(item->getItemQuantity()) + "</quantity>\n");
        xml.append("            <type>" + SaveSystem::typeToString(item->getType()) + "</type>\n");
        xml.append("        </item>\n");
    }
    xml.append("    </inventoryData>\n");

    // TODO: Object data
    xml.append("    <objectData>\n");

    std::string savePools[] = {"boar", "crate", "wall", "zombie"};

    if (std::filesystem::exists("../../Resources/Saves/save.xml")) {
        auto save = Save::save_(file);

        for (auto object : save->objectData().object()) {
            if (object.level() == game->getLevel()._levelName) continue;

            xml.append("        <object>\n");
            xml.append("            <type>" + object.type() + "</type>\n");
            xml.append("            <level>" + object.level() + "</level>\n");
            xml.append("            <common:position>\n");
            xml.append("                <x>" + std::to_string(object.position().x()) + "</x>\n");
            xml.append("                <y>" + std::to_string(object.position().y()) + "</y>\n");
            xml.append("            </common:position>\n");
            xml.append("        </object>\n");
        }
    }


    for (const std::string &pool : savePools) {
        for (auto *poolItem : game->getPoolLevel()->getPool(pool).entitiesInUse) {
            xml.append("        <object>\n");
            xml.append("            <type>" + pool + "</type>\n");
            xml.append("            <level>" + game->getLevel()._levelName + "</level>\n");
            xml.append("            <common:position>\n");
            xml.append(
                    "                <x>" +
                    std::to_string(poolItem->getComponent<TransformComponent>()->getPosition().x) +
                    "</x>\n");
            xml.append(
                    "                <y>" +
                    std::to_string(poolItem->getComponent<TransformComponent>()->getPosition().y) +
                    "</y>\n");
            xml.append("            </common:position>\n");
            xml.append("        </object>\n");
        }
    }


    xml.append("    </objectData>\n");



    // END FILE
    xml.append("</sv:save>");

    std::ofstream SaveFile(file);

    SaveFile << xml;

    SaveFile.close();

}

std::string SaveSystem::typeToString(EntityObject::EntityType type) {
    switch (type) {
        case EntityObject::weapon:
            return "weapon";
        case EntityObject::resource:
            return "resource";
        case EntityObject::object:
            return "object";
    }

    return "";
}

void SaveSystem::clearSave() {
    std::filesystem::remove("../../Resources/Saves/save.xml");
}



