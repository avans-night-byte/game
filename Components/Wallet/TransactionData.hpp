#pragma once
#include <vector>

#include "../Inventory/InventoryItem.hpp"


class TransactionData {

private:
    int _experience = 0;
    int _zombytes = 0;
    int _score = 0;

    std::vector<InventoryItem*> _transactionItems;
    std::function<void(TransactionData)> _callback = nullptr;

public:
    TransactionData(int experience, int zombytes, int score);
    TransactionData(int experience, int zombytes, int score, std::vector<InventoryItem*> items);

    [[nodiscard]] int getExperience() const;
    [[nodiscard]] int getScore() const;
    [[nodiscard]] int getZombytes() const;

    void completeTransaction(TransactionData &data);
    void setTransactionCallback(const std::function<void(TransactionData)> &function);
};


