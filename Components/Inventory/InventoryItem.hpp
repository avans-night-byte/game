#pragma once

#include <string>
#include "../../../API//Helpers/Vector2.hpp"
#include "../EntityObject.hpp"

class InventoryItem {
public:

private:
    Vector2 _position {};
    Vector2 _index {};

    int _quantity = 0;

    std::string _name {};
    EntityObject::EntityType _type {};

public:
    InventoryItem(int quantity, std::string name, EntityObject::EntityType type);

    std::string getName();
    Vector2 &getPosition();
    Vector2 &getIndex();
    EntityObject::EntityType &getType();


    [[nodiscard]] int getItemQuantity() const;
    int addItemQuantity(int quantity);

    void setIndex(Vector2 &value);

    void setPosition(Vector2 &value);

    int removeItemQuantity(int quantity);

};


