#pragma once


#include <string>
#include <map>
#include <memory>
#include "InventoryItem.hpp"

#include "../Rendering/RenderComponent.hpp"
#include "../TransformComponent.hpp"
#include "../../Engine/Input/Input.hpp"
#include "../../../Engine/Rendering/TextWrapper.hpp"
#include "../../../API//Helpers/Event.h"


class InventoryComponent : public Component {

    std::unique_ptr<TransformComponent> _transformComponent = nullptr;
    std::unique_ptr<RenderComponent> _renderComponent = nullptr;

    const int _rows = 5;
    const int _columns = 5;

    const float _offset = 125;

    const float _startX = 450;
    const float _startY = 200;

    bool _isOpen = false;

    Vector2 _emptySlot {};

    std::vector<InventoryItem*> _inventory {};
    std::map<std::string, TextWrapper*> _quantityText {};

    Event<InventoryItem&> _onInventoryClickEvent {};

    RenderingAPI &_renderingAPI;

public:

    explicit InventoryComponent(EntityId id);

    ~InventoryComponent() override;

    void render() override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void postInitialize(EntityObject &entityObject) override;

    void update(const Input &inputSystem) override;

    void addEntityToInventory(EntityObject &e);

    void addToInventory(InventoryItem *item);

    std::vector<InventoryItem *> &getInventoryItems();

    void removeFromInventory(const std::string &name, int count);

    void showInventory();

    void hideInventory();

    void click(const Input &input);

    [[nodiscard]] int getInventorySize() const;

    [[nodiscard]] bool isInventoryOpen() const;

    Event<InventoryItem&> &getOnInventoryClickEventManager();

private:
    InventoryItem *findInventoryItem(const std::string &name);

    InventoryItem *findInventoryItem(Vector2 &index);

    bool findEmptySlot();

    bool checkItemIfEmpty(const std::string &name);

};