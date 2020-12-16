#pragma once

#include <string>
#include "../../../API//Helpers/Vector2.hpp"

class InventoryItem {
public:
    //Weapons = Pistol, RPG etc
    //Resource = Water, Cookie, etc,
    //Object = Wall, Turret, Box, etc
    enum itemType { weapon, resource, object };
private:
    Vector2 _position;
    Vector2 _index;

    int _quantity;

    std::string _name;
    itemType _type;

public:
    InventoryItem(int quantity, std::string name, itemType type);

    void onClick();

    std::string getName();
    Vector2 &getPosition();
    Vector2 &getIndex();

    [[nodiscard]] int getItemQuantity() const;
    int addItemQuantity(int quantity);

    void setIndex(Vector2 &value);

    void setPosition(Vector2 &value);
};


