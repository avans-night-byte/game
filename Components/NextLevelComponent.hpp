#pragma once


#include <string>
#include "../../Engine/Physics/ContactHandler.hpp"

// TODO: Don't use ContactHandler of Engine but of API (which does not exist yet).
class NextLevelComponent : public ContactHandler {
public:
    std::string NextLevel = "Wow look at me!";

    void startContact() override;

    void endContact() override;
};


