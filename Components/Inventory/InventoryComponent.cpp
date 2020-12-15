
#include "InventoryComponent.hpp"
#include "../../Game.hpp"


InventoryComponent::InventoryComponent(EntityId id) : Component(id), _renderingAPI(Game::getInstance()->getRenderingApi()) {
    _transformComponent = std::make_unique<TransformComponent>(id);

    _renderingAPI.loadTexture("../../Resources/Sprites/inventory_slot.png", "InventorySlot");
    _renderingAPI.loadTexture("../../Resources/Sprites/Wooden_Crate.png", "crate");

    _quantityText = std::map<std::string, TextWrapper*>();

    //Init inventory
    for (int x = 1; x < _rows; ++x) {
        for (int y = 1; y < _columns; ++y) {
            Vector2 position =  {_startX + (_offset * x), _startY + (_offset * y)};
            Vector2 index(x, y);
            addToInventory(new InventoryItem{position, index, 10, "crate", InventoryItem::object});
        }
    }
}

void InventoryComponent::initialize(EntityObject &entityParent) {


}

void InventoryComponent::render() {

    if(_isOpen){

        for (int x = 1; x < _rows; ++x) {
            for (int y = 1; y < _columns; ++y) {
                _renderingAPI.drawTexture("InventorySlot", _startX + (_offset * x), _startY + (_offset * y), 125, 125, 1, 0);
            }
        }

        for (auto & it : _inventory) {
            InventoryItem item = *it;
            _renderingAPI.drawTexture(item.getName(), item.getPosition().x, item.getPosition().y, 125, 125, 1, 0);
            _quantityText[item.getName() + "_quantity"]->render(item.getPosition().x, item.getPosition().y);

        }
    }
}

void InventoryComponent::update(const Input &inputSystem) {

    if(inputSystem.keyMap.action == "INVENTORY"){
        _isOpen = true;
    }

}

void InventoryComponent::fixedUpdate(const float &deltaTime) {

}

std::string InventoryComponent::name() const {
    return "InventoryComponent";
}

Component *InventoryComponent::clone(EntityId entityId, const Components::component *component) {
    return nullptr;
}

void InventoryComponent::removeFromInventory(std::string &name, int count) {
    auto foundItem = findInventoryItem(name);
    if(foundItem == nullptr) return;

    foundItem->addItemQuantity(-count);
    if(foundItem->getItemQuantity() < 1) _inventory.erase(_inventory.begin() + (foundItem->getIndex().x + foundItem->getIndex().y));
}

void InventoryComponent::addToInventory(InventoryItem *item) {
    if(_inventory.size() >= getInventorySize()) return;

    auto foundItem = findInventoryItem(item->getName());
    if(foundItem != nullptr){
        foundItem->addItemQuantity(item->getItemQuantity());
        return;
    }
    _inventory.push_back(item);
    auto wrapper = TextWrapper::createText(_renderingAPI, std::to_string(item->getItemQuantity()), "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", item->getName() + "_quantity");
    _quantityText[item->getName() + "_quantity"] = wrapper;
}


int InventoryComponent::getInventorySize() const {
    return (_columns + _rows);
}

InventoryItem *InventoryComponent::findInventoryItem(const std::string &name){
    for (auto &it : _inventory) {
        if(it->getName() == name) return it;
    }
    return nullptr;
}




