#include "InventoryItem.hpp"

#include <utility>


InventoryItem::InventoryItem(Vector2 &position, Vector2 &index, int count, std::string name, itemType type) : _position(position), _index(index), _quantity(count), _name(std::move(name)), _type(type) {}

void InventoryItem::onClick() {
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

int InventoryItem::addItemQuantity(int quantity) const {
    _quantity + quantity;
    return _quantity;
}



