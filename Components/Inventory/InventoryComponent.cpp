
#include "InventoryComponent.hpp"
#include "../../Game.hpp"


InventoryComponent::InventoryComponent(EntityId id) : Component(id), _renderingAPI(Game::getInstance()->getRenderingApi()) {
    _transformComponent = std::make_unique<TransformComponent>(id);

    _renderingAPI.loadTexture("../../Resources/Sprites/inventory_slot.png", "InventorySlot");
    _renderingAPI.loadTexture("../../Resources/Sprites/Wooden_Crate.png", "crate");
    _renderingAPI.loadTexture("../../Resources/Sprites/boar.png", "boar");

    _quantityText = std::map<std::string, TextWrapper*>();

    _emptySlot = Vector2(1,1);

    //Init inventory
    for (int x = 1; x < _rows; ++x) {
        for (int y = 1; y < _columns; ++y) {
            Vector2 position =  {_startX + (_offset * x), _startY + (_offset * y)};
            Vector2 index(x, y);

            addToInventory(new InventoryItem{ 10, "crate", InventoryItem::object});
            addToInventory(new InventoryItem{ 1, "crate", InventoryItem::object});
            addToInventory(new InventoryItem{10, "boar", InventoryItem::object});
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
            std::string key = item.getName() + "_quantity_" + std::to_string(item.getItemQuantity());

            //Als de nummer nog niet in de wrapper staat dan voeg je hem toe
            if(_quantityText[key] == nullptr){
                auto wrapper = TextWrapper::createText(_renderingAPI, std::to_string(item.getItemQuantity()), "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", key);
                _quantityText[key] = wrapper;
            }

            _quantityText[key]->render(item.getPosition().x, item.getPosition().y);
        }
    }
}

void InventoryComponent::update(const Input &inputSystem) {

    if(inputSystem.keyMap.action == "INVENTORY"){
        _isOpen = true;
    }

    if(inputSystem.keyMap.code == "MOUSE_BUTTON_LEFT"){

        _isOpen = false;
        onClick(inputSystem);
    }

}

void InventoryComponent::onClick(const Input &input){
    float width = 125;
    float height = 125;

    for (auto &it : _inventory) {
        auto pos = it->getPosition();
        if (pos.x <= input.x && pos.y <= input.y && pos.x + width >= input.x && pos.y + height >= input.y) {
            _onInventoryClickEvent(*it);
            checkItemIfEmpty(it->getName());
        }
    }
}

void InventoryComponent::fixedUpdate(const float &deltaTime) {

}

std::string InventoryComponent::name() const {
    return "InventoryComponent";
}

Component *InventoryComponent::build(EntityId entityId, const Components::component *component) {
    return nullptr;
}

void InventoryComponent::removeFromInventory(const std::string &name, int count) {
    auto foundItem = findInventoryItem(name);
    if(foundItem == nullptr) return;

    foundItem->addItemQuantity(-count);
    if(foundItem->getItemQuantity() < 1) _inventory.erase(_inventory.begin() + (foundItem->getIndex().x -1 + foundItem->getIndex().y -1));

    findEmptySlot();
}

void InventoryComponent::checkItemIfEmpty(const std::string &name) {
    auto foundItem = findInventoryItem(name);
    if(foundItem == nullptr) return;

    if(foundItem->getItemQuantity() < 1) _inventory.erase(_inventory.begin() + (foundItem->getIndex().x -1 + foundItem->getIndex().y -1));

    findEmptySlot();
}

void InventoryComponent::addToInventory(InventoryItem *item) {
    if(_inventory.size() >= getInventorySize()) return;

    auto foundItem = findInventoryItem(item->getName());
    if(foundItem != nullptr){
        foundItem->addItemQuantity(item->getItemQuantity());
        return;
    }

    findEmptySlot();

    item->setIndex(_emptySlot);

    Vector2 position =  {_startX + (_offset * _emptySlot.x), _startY + (_offset * _emptySlot.y)};
    item->setPosition(position);

    _inventory.push_back(item);

}


int InventoryComponent::getInventorySize() const {
    return (_columns + _rows);
}

bool InventoryComponent::findEmptySlot(){
    for (int x = 1; x < _rows; ++x) {
        for (int y = 1; y < _columns; ++y) {
            Vector2 index(y, x);
            auto item = findInventoryItem(index);
            if(item != nullptr) continue;

            _emptySlot = index;
            return true;
        }
    }
    return false;
}

InventoryItem *InventoryComponent::findInventoryItem(const std::string &name){
    for (auto &it : _inventory) {
        if(it->getName() == name) return it;
    }
    return nullptr;
}

InventoryItem *InventoryComponent::findInventoryItem(Vector2 &index){
    for (auto &it : _inventory) {
        auto i = it->getIndex();
        if(it->getIndex() == index) return it;
    }
    return nullptr;
}


bool InventoryComponent::isMenuOpen() const {
    return _isOpen;
}

Event<InventoryItem&> &InventoryComponent::getEventManager() {
    return _onInventoryClickEvent;
}



