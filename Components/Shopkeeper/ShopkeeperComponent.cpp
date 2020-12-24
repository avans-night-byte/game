#include "ShopkeeperComponent.hpp"

void ShopkeeperComponent::initialize(EntityObject &entityParent) {

    _inventoryComponent = entityParent.getComponent<InventoryComponent>();
    _tradingComponent = entityParent.getComponent<TradingComponent>();
    _transformComponent = entityParent.getComponent<TransformComponent>();
    _physicsComponent = entityParent.getComponent<PhysicsComponent>();
    _physicsComponent->collisionHandlers.push_back(this);
    _renderComponent = entityParent.getComponent<RenderComponent>();

    _inventoryComponent->getOnInventoryClickEventManager() += std::bind(&TradingComponent::onItemSelect, _tradingComponent, std::placeholders::_1);
}

void ShopkeeperComponent::startTransaction() {
    _inventoryComponent->showInventory();
}

void ShopkeeperComponent::render() {

}

void ShopkeeperComponent::update(const Input &inputSystem) {

}

void ShopkeeperComponent::fixedUpdate(const float &deltaTime) {

}

std::string ShopkeeperComponent::name() const {
    return "ShopkeeperComponent";
}

Component *ShopkeeperComponent::build(EntityId entityId, const Components::component *component) {
    return nullptr;
}

void ShopkeeperComponent::onCollisionEnter(EntityObject *self, EntityObject *other) {
    auto otherTrading = other->getComponent<TradingComponent>();
    if(otherTrading == nullptr) return;
    _tradingComponent->isTradable(true);
}

void ShopkeeperComponent::onCollisionExit(EntityObject *self, EntityObject *other) {
    auto otherTrading = other->getComponent<TradingComponent>();
    if(otherTrading == nullptr) return;
    _tradingComponent->isTradable(false);
}

ShopkeeperComponent::~ShopkeeperComponent() {
    delete _physicsComponent;
    delete _inventoryComponent;
    delete _transformComponent;
    delete _renderComponent;
}




