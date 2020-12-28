#pragma once

#include "../Wallet/TransactionData.hpp"
#include "../../API/Helpers/Event.h"
#include "../../../Engine/Rendering/TextWrapper.hpp"

class TradingComponent : public Component {

private:

    //TODO: Cancle transaction
    //TODO: Clean when transaction completed

    Event<bool> _onTradeFinishedEventHandler {};

    std::map<InventoryItem*, int> _buyableItems{};
    std::vector<InventoryItem *> _selectedItems{};
    std::map<std::string, TextWrapper*> _tradingText {};

    RenderingAPI *_renderAPI = nullptr;
    EntityObject *_parent = nullptr;

    bool _isTradable = false;

    TransactionData _otherTransactionData { 0, 0, 0 };

public:
    explicit TradingComponent(EntityId id);

    ~TradingComponent() override;

    void onItemSelect(InventoryItem &item);

    int calculateItems();

    void onClick(const Input &inputSystem);

    void startTransaction(TransactionData &data);

    void finishTransaction();

    Event<bool> &getOnTransactionFinishedEventManager();

    [[nodiscard]] bool isTradable() const;
    bool isTradable(bool b);


public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void postInitialize(EntityObject &entityObject) override;

};


