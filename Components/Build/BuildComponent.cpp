#include "BuildComponent.hpp"


BuildComponent::BuildComponent(EntityId id) : Component(id), _poolLevel(*Game::getInstance()->getPoolLevel()) {}

void BuildComponent::initialize(EntityObject &entityParent) {}

void BuildComponent::update(const Input &inputSystem) {}

void BuildComponent::fixedUpdate(const float &deltaTime) {}

std::string BuildComponent::name() const {
    return "BuildComponent";
}

Component *BuildComponent::build(EntityId entityId, const Components::component *component) {
    return new BuildComponent(entityId);
}

void BuildComponent::pickUpObject(EntityObject &entity) {
    _pickUpEntityEventHandler(entity);
}

void BuildComponent::placeObject(const TransformComponent &transform, const Input &inputSystem) {

    if (_selectedObject == nullptr || _selectedObject->getItemQuantity() < 1) return;

    EntityObject &placeable = _poolLevel.getPool(_selectedObject->getName()).getEntity();

    PhysicsComponent *physicsComponent = placeable.getPhysicsComponent();
    Game::getInstance()->addEventBodyHandler([physicsComponent] { physicsComponent->setEnabled(true); });

    physicsComponent->setTransform(Vector2(inputSystem.x, inputSystem.y), false);

    _selectedObject->removeItemQuantity(1);
}


void BuildComponent::setBuildObject(InventoryItem &item) {
    _selectedObject = &item;
}

void BuildComponent::render() {

}

Event<EntityObject &> &BuildComponent::getPickupEventHandler() {
    return _pickUpEntityEventHandler;
}

void BuildComponent::postInitialize(EntityObject &entityObject) {

}



