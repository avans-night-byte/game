#pragma once

#include <string>
#include "../../../Engine/Helpers/Vector2.hpp"

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
    InventoryItem(Vector2 &position, Vector2 &index, int count, std::string name, itemType type);

    void onClick();

    std::string getName();
    Vector2 &getPosition();
    Vector2 &getIndex();

    [[nodiscard]] int getItemQuantity() const;
    int addItemQuantity(int quantity) const;
};


