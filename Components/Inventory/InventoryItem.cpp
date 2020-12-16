#include "InventoryItem.hpp"

#include <utility>


InventoryItem::InventoryItem(int count, std::string name, itemType type) : _quantity(count), _name(std::move(name)), _type(type) {}

void InventoryItem::setIndex(Vector2 &value){
    _index = value;
}

void InventoryItem::setPosition(Vector2 &value){
    _position = value;
}

std::string InventoryItem::getName() {
    return _name;
}

Vector2 &InventoryItem::getPosition() {
    return _position;
}

Vector2 &InventoryItem::getIndex() {
    return _index;
}

int InventoryItem::getItemQuantity() const{
    return _quantity;
}

int InventoryItem::addItemQuantity(int quantity) {
    _quantity += quantity;
    return _quantity;
}



