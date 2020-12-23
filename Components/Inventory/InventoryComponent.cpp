
#include "InventoryComponent.hpp"
#include "../../Game.hpp"


InventoryComponent::InventoryComponent(EntityId id) : Component(id), _renderingAPI(Game::getInstance()->getRenderingApi()) {
    _transformComponent = std::make_unique<TransformComponent>(id);
    _quantityText = std::map<std::string, TextWrapper*>();
    _emptySlot = Vector2(1,1);

    addToInventory(new InventoryItem{100, "crate", EntityObject::EntityType::object});
    addToInventory(new InventoryItem{50, "crate", EntityObject::EntityType::object});
    addToInventory(new InventoryItem{2, "boar", EntityObject::EntityType::resource});
}

void InventoryComponent::initialize(EntityObject &entityParent) {


}

void InventoryComponent::render() {

    if(_isOpen){

        for (int x = 1; x < _rows; ++x) {
            for (int y = 1; y < _columns; ++y) {
                _renderingAPI.drawTexture("inventory_slot", _startX + (_offset * x), _startY + (_offset * y), 125, 125, 1, 0);
            }
        }

        for (auto & it : _inventory) {
            InventoryItem item = *it;

            if(checkItemIfEmpty(item.getName())) continue;

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

    //TODO: parent component needs to tell the inventory when to open
   /* if(inputSystem.keyMap.action == "INVENTORY"){
        _isOpen = true;
    }

    if(inputSystem.keyMap.code == "MOUSE_BUTTON_LEFT"){
        _isOpen = false;
        onClick(inputSystem);
    }*/
}

void InventoryComponent::showInventory(){
    _isOpen = true;
}

void InventoryComponent::hideInventory(){
    _isOpen = false;
}

void InventoryComponent::click(const Input &input){

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

bool InventoryComponent::checkItemIfEmpty(const std::string &name) {
    auto foundItem = findInventoryItem(name);
    if(foundItem == nullptr) return true;

    if(foundItem->getItemQuantity() < 1) {
        _inventory.erase(_inventory.begin() + (foundItem->getIndex().x -1 + foundItem->getIndex().y -1));
        findEmptySlot();
        return true;
    }
    return false;
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

void InventoryComponent::addEntityToInventory(EntityObject &e) {
    if(e.getType() == EntityObject::EntityType::level_change ||
            e.getType() == EntityObject::EntityType::character) return;

    auto &id = e.getComponent<RenderComponent>()->getSpriteID();
    auto *item = new InventoryItem { 1, id, e.getType()};


    if(_inventory.size() >= getInventorySize() || item->getName().empty()) return;

    auto foundItem = findInventoryItem(id);
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


std::vector<InventoryItem *> &InventoryComponent::getInventoryItems() {
    return _inventory;
}

InventoryItem *InventoryComponent::findInventoryItem(const std::string &name){
    for (auto &it : _inventory) {
        if(it->getName() == name) return it;
    }
    return nullptr;
}

InventoryItem *InventoryComponent::findInventoryItem(Vector2 &index){
    for (auto &it : _inventory) {
        if(it->getIndex() == index) return it;
    }
    return nullptr;
}

bool InventoryComponent::isInventoryOpen() const {
    return _isOpen;
}

Event<InventoryItem&> &InventoryComponent::getOnInventoryClickEventManager() {
    return _onInventoryClickEvent;
}

InventoryComponent::~InventoryComponent() {
    _inventory.clear();
}





