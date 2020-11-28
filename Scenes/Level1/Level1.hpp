//
// Created by sascha on 11/27/20.
//

#ifndef NIGHTBYTE_LEVEL1_HPP
#define NIGHTBYTE_LEVEL1_HPP


#include "../../../Engine/Rendering/Level.hpp"

class Level1 {
private:
    Level* _level;
public:
    Level1(EngineRenderingAPI& engineRenderingApi);
    ~Level1();
    void render(EngineRenderingAPI& engineRenderingAPI);
};


#endif //NIGHTBYTE_LEVEL1_HPP
