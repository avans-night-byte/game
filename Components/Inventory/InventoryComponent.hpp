#pragma once


#include <string>
#include <map>
#include <memory>
#include "InventoryItem.hpp"

#include "../RenderComponent.hpp"
#include "../TransformComponent.hpp"
#include "../../Engine/Input/Input.hpp"
#include "../../../Engine/Rendering/TextWrapper.hpp"
#include "../../../Engine/Helpers/Event.h"


class InventoryComponent : public Component {

    std::unique_ptr<TransformComponent> _transformComponent;
    std::unique_ptr<RenderComponent> _renderComponent;

    const int _rows = 5;
    const int _columns = 5;

    const float _offset = 125;

    const float _startX = 450;
    const float _startY = 200;

    bool _isOpen = false;

    Vector2 _emptySlot;

    std::vector<InventoryItem*> _inventory;
    std::map<std::string, TextWrapper*> _quantityText;

    Event<InventoryItem&> _onInventoryClickEvent;

    RenderingAPI &_renderingAPI;

public:

    explicit InventoryComponent(EntityId id);

    void render() override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *clone(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void update(const Input &inputSystem) override;

    void addToInventory(InventoryItem *item);

    void removeFromInventory(const std::string &name, int count);

    [[nodiscard]] int getInventorySize() const;

    [[nodiscard]] bool isMenuOpen() const;

    Event<InventoryItem&> &getEventManager();

private:
    InventoryItem *findInventoryItem(const std::string &name);

    InventoryItem *findInventoryItem(Vector2 &index);

    bool findEmptySlot();

    void onClick(const Input &input);

    void checkItemIfEmpty(const std::string &name);

};