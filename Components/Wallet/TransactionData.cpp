#include "TransactionData.hpp"

#include <utility>

TransactionData::TransactionData(int experience, int zombytes, int score) {
    _experience = experience;
    _zombytes = zombytes;
    _score = score;
}

TransactionData::TransactionData(int experience, int zombytes, int score, std::vector<InventoryItem*> items) {
    _experience = experience;
    _zombytes = zombytes;
    _score = score;
    _transactionItems = std::move(items);
}

void TransactionData::setTransactionCallback(const std::function<void(TransactionData&)> &function){
    _callback = function;
}

int TransactionData::getExperience() const {
    return _experience;
}

int TransactionData::getScore() const {
    return _score;
}

int TransactionData::getZombytes() const {
    return _zombytes;
}

std::vector<InventoryItem *> TransactionData::getInventoryItems() {
    return _transactionItems;
}


void TransactionData::returnTransaction(TransactionData &data) {
    if(_callback == nullptr) return;
    _callback(data);
}



