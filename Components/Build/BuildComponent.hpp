#pragma once

#include "../Inventory/InventoryItem.hpp"
#include "../EntityObject.hpp"
#include "../../API/Helpers/Event.h"

class BuildComponent : public Component {

private:
    Event<EntityObject&> _pickUpEntityEventHandler;
public:
    BuildComponent();
    void placeObject(EntityObject& entity);
    void createEntityObject(InventoryItem &item);

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    std::string name() const override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    Event<EntityObject&> getPickupEventHanlder();

};


