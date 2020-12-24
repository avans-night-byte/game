#pragma once

#include "../Wallet/TransactionData.hpp"
#include "../../API/Helpers/Event.h"

class TradingComponent : public Component {

private:
    Event<TransactionData> _transactionEventHandler {};

    //TODO: Cancle transaction
    //TODO: Clean when transaction completed

    std::map<InventoryItem*, int> _buyableItems;
    std::vector<InventoryItem *> _selectedItems;

    bool _isTradable = false;
public:
    explicit TradingComponent(EntityId id);

    ~TradingComponent() override;

    void onItemSelect(InventoryItem &item);

    [[nodiscard]] bool isTradable() const;
    bool isTradable(bool b);


public:
    void render() override;

    void update(const Input &inputSystem) override;

    void fixedUpdate(const float &deltaTime) override;

    [[nodiscard]] std::string name() const override;

    Component *build(EntityId entityId, const Components::component *component) override;

    void initialize(EntityObject &entityParent) override;

    void startTransaction(TransactionData &data);
};


