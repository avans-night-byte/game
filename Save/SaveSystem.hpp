#pragma once

#include <string>
#include "../Components/EntityObject.hpp"

class SaveSystem {
private:
    static std::string typeToString(EntityObject::EntityType type);
public:
    static void loadSave(const std::string& file);

    static void saveSave(const std::string &file);
};