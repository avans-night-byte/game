#pragma once

#include <string>

class LevelBase {



    LevelBase(std::string resourcePath) {

    }

    virtual void initialize() = 0;

    virtual void update() = 0;

    virtual void fixedUpdate() = 0;
};