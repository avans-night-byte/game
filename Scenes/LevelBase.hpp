#pragma once

#include <string>

using namespace std;

class LevelBase {



    LevelBase(string resourcePath) {

    }

    virtual void initialize() = 0;

    virtual void update() = 0;

    virtual void fixedUpdate() = 0;
};