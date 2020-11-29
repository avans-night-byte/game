#pragma once


#include <string>
#include "../../Engine/Physics/ContactHandler.hpp"

// TODO: Don't use ContactHandler of Engine
class NextLevelComponent : public ContactHandler {
public:
    std::string NextLevel = "Wow look at me!";

    void startContact() override;

    void endContact() override;
};


