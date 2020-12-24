#pragma once

#include "../Inventory/InventoryItem.hpp"
#include "../EntityObject.hpp"
#include "../../API/Helpers/Event.h"
#include "../../Object/Pool.hpp"
#include "../../Scenes/PoolLevel.hpp"
#include "../Component.hpp"
#include "../TransformComponent.hpp"
#include "../../Game.hpp"

class BuildComponent : public Component {

private:
    Event<EntityObject&> _pickUpEntityEventHandler {};

    PoolLevel &_poolLevel;

    InventoryItem *_selectedObject = nullptr;

public:
    explicit BuildComponent(EntityId id);

    void placeObject(const TransformComponent &transform);

    void pickUpObject(EntityObject &entity);

    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    Event<EntityObject&> &getPickupEventHandler();

    void setBuildObject(InventoryItem &item);


};


