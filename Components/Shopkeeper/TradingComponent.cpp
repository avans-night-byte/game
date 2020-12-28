#include "TradingComponent.hpp"
#include "../Inventory/InventoryComponent.hpp"
#include "../../Game.hpp"

TradingComponent::TradingComponent(EntityId id) : Component(id) {
}

void TradingComponent::onItemSelect(InventoryItem &item) {
    auto it = std::find(_selectedItems.begin(), _selectedItems.end(), &item);
    if(it != _selectedItems.end()){
        _selectedItems.erase(it);
        return;
    }
    _selectedItems.push_back(&item);
}

void TradingComponent::startTransaction(TransactionData &data){
    _otherTransactionData = data;
    auto inventoryComponent = _parent->getComponent<InventoryComponent>();

    int cost = 10;

    for(InventoryItem *item : inventoryComponent->getInventoryItems()){
        int totalCost = (item->getItemQuantity() * cost);
        _buyableItems[item] = totalCost;
    }
}

void TradingComponent::finishTransaction(){
    int totalCost = calculateItems();

    TransactionData returnTransaction(200, -totalCost, 100, _selectedItems);

    if(_otherTransactionData.getZombytes() < totalCost || (totalCost < 1 && _selectedItems.empty())){
        returnTransaction = { 0, 0, 0 };
    }

    _otherTransactionData.returnTransaction(returnTransaction);
    _selectedItems.clear();
}

int TradingComponent::calculateItems(){
    int totalCost = 0;
    for (InventoryItem *item : _selectedItems) {
        totalCost += _buyableItems[item];
    }
    return totalCost;
}

void TradingComponent::render(){
    if(_isTradable){

        auto &renderApi = Game::getInstance()->getRenderingApi();

        Vector2 position(825, 850);
        renderApi.drawRectangle(position, 250, 70, "000000", 100);

        std::string money = "money_" + std::to_string(_otherTransactionData.getZombytes() - calculateItems());

        if(_tradingText[money] == nullptr){
            auto wrapper = TextWrapper::createText(*_renderAPI, "Money left:" + std::to_string( _otherTransactionData.getZombytes() - calculateItems()), "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", money);
            _tradingText[money] = wrapper;
        }
        _tradingText["welcome_store"]->render(570, 300);
        _tradingText["pay_store"]->render(930, 870);
        _tradingText[money]->render(570, 850);


        for (auto &item : _selectedItems) {
            renderApi.drawRectangle(item->getPosition(), 125, 125, "ff0000", 100);
        }

    }
}

void TradingComponent::update(const Input &inputSystem) {
    onClick(inputSystem);
}

void TradingComponent::onClick(const Input &inputSystem){
    if(inputSystem.x == -1 || inputSystem.y == -1) return;

    if(inputSystem.x >= 825 && inputSystem.y >= 850 && inputSystem.x <= 1075 && inputSystem.y <= 920){
        _onTradeFinishedEventHandler(true);
    }
}

void TradingComponent::fixedUpdate(const float &deltaTime) {

}

std::string TradingComponent::name() const {
    return "TradingComponent";
}

Component *TradingComponent::build(EntityId entityId, const Components::component *component) {
    return new TradingComponent(entityId);
}

void TradingComponent::initialize(EntityObject &entityParent) {

    _parent = &entityParent;
    _renderAPI = &Game::getInstance()->getRenderingApi();

    std::string welcome = "welcome_store";
    std::string pay = "pay_store";

    auto wrapper = TextWrapper::createText(*_renderAPI, "Welcome to the store!", "../../Resources/Fonts/LiberationMono-Regular.ttf", 20, "ffffff", welcome);
    _tradingText[welcome] = wrapper;

    wrapper = TextWrapper::createText(*_renderAPI, "Pay", "../../Resources/Fonts/LiberationMono-Regular.ttf", 30, "ffffff", pay);
    _tradingText[pay] = wrapper;
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

Event<bool> &TradingComponent::getOnTransactionFinishedEventManager() {
    return _onTradeFinishedEventHandler;
}

void TradingComponent::postInitialize(EntityObject &entityObject) {

}


