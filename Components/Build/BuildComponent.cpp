#include "BuildComponent.hpp"

BuildComponent::BuildComponent() {

}

void BuildComponent::initialize(EntityObject &entityParent) {

}

void BuildComponent::placeObject(EntityObject &entity) {

}

void BuildComponent::createEntityObject(InventoryItem &item) {

}

void BuildComponent::render() {

}

void BuildComponent::update(const Input &inputSystem) {

}

void BuildComponent::fixedUpdate(const float &deltaTime) {

}

std::string BuildComponent::name() const {
    return "BuildComponent";
}

Component *BuildComponent::build(EntityId entityId, const Components::component *component) {
    return nullptr;
}


Event<EntityObject &> BuildComponent::getPickupEventHanlder() {
    return _pickUpEntityEventHandler;
}
