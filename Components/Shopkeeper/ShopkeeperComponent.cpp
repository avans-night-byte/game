#include "ShopkeeperComponent.hpp"
#include "../../Game.hpp"

void ShopkeeperComponent::initialize(EntityObject &entityParent) {

    _inventoryComponent = entityParent.getComponent<InventoryComponent>();
    _tradingComponent = entityParent.getComponent<TradingComponent>();
    _transformComponent = entityParent.getComponent<TransformComponent>();
    _physicsComponent = entityParent.getComponent<PhysicsComponent>();
    _physicsComponent->collisionHandlers.push_back(this);
    _renderComponent = entityParent.getComponent<RenderComponent>();

    _inventoryComponent->addToInventory(new InventoryItem{150, "crate", EntityObject::EntityType::object});
    _inventoryComponent->addToInventory(new InventoryItem{20, "wall", EntityObject::EntityType::object});
    _inventoryComponent->addToInventory(new InventoryItem{2, "boar", EntityObject::EntityType::resource});

    _inventoryComponent->getOnInventoryClickEventManager() += std::bind(&TradingComponent::onItemSelect, _tradingComponent, std::placeholders::_1);
    _tradingComponent->getOnTransactionFinishedEventManager() += std::bind(&ShopkeeperComponent::finishTransaction, this, std::placeholders::_1);
}

void ShopkeeperComponent::startTransaction(TransactionData &data) {
    if(_startedTransaction) return;

    Game::getInstance()->getAudioAPI().playFromMemory("welcome");

    _inventoryComponent->showInventory();
    _tradingComponent->startTransaction(data);
    _startedTransaction = _tradingComponent->isTradable(true);
}

bool ShopkeeperComponent::startedTransaction() const{
    return _startedTransaction;
}

void ShopkeeperComponent::finishTransaction(bool b){

    _inventoryComponent->hideInventory();
    _tradingComponent->finishTransaction();
    _startedTransaction = _tradingComponent->isTradable(false);

    Game::getInstance()->getAudioAPI().playFromMemory("comeback");
}

void ShopkeeperComponent::render() {

}

void ShopkeeperComponent::update(const Input &inputSystem) {
    if(_inventoryComponent->isInventoryOpen()){
        if(inputSystem.keyMap.code == "MOUSE_BUTTON_LEFT" ){
            _inventoryComponent->click(inputSystem);
        }
    }

}

void ShopkeeperComponent::fixedUpdate(const float &deltaTime) {

}

std::string ShopkeeperComponent::name() const {
    return "ShopkeeperComponent";
}

Component *ShopkeeperComponent::build(EntityId entityId, const Components::component *component) {
    return new ShopkeeperComponent(entityId);
}

void ShopkeeperComponent::onCollisionEnter(EntityObject *self, EntityObject *other) {
    if(other == nullptr)
        return;
}

void ShopkeeperComponent::onCollisionExit(EntityObject *self, EntityObject *other) {
    if(other == nullptr)
        return;
}

void ShopkeeperComponent::postInitialize(EntityObject &entityObject) {

}




