#include "TradingComponent.hpp"

TradingComponent::TradingComponent(EntityId id, std::vector<InventoryItem*> &items) : Component(id) {
    int cost = 10;

    for(InventoryItem *item : items){
        int totalCost = (item->getItemQuantity() * cost);
        _buyableItems[item] = totalCost;
    }
}

void TradingComponent::onItemSelect(InventoryItem &item) {
    auto it = std::find(_selectedItems.begin(), _selectedItems.end(), &item);
    if(it != _selectedItems.end()){
        _selectedItems.erase(it);
    }
    _selectedItems.push_back(&item);
}

void TradingComponent::startTransaction(TransactionData &data){
    int totalCost = 0;

    for (InventoryItem *item : _selectedItems) {
        totalCost += _buyableItems[item];
    }

    if(data.getZombytes() < totalCost || totalCost < 1) return;

    TransactionData returnTransaction(200, 0, 100, _selectedItems);
    data.completeTransaction(returnTransaction);
}

void TradingComponent::render() {
        //TODO: Draw buy button so player can finish transaction


}

void TradingComponent::update(const Input &inputSystem) {

}

void TradingComponent::fixedUpdate(const float &deltaTime) {

}

std::string TradingComponent::name() const {
    return "TradingComponent";
}

Component *TradingComponent::build(EntityId entityId, const Components::component *component) {
    return nullptr;
}

void TradingComponent::initialize(EntityObject &entityParent) {

}

TradingComponent::~TradingComponent() {
    _buyableItems.clear();
    _selectedItems.clear();
}

bool TradingComponent::isTradable() const {
    return _isTradable;
}

bool TradingComponent::isTradable(bool b) {
    return _isTradable = b;
}


