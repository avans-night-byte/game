#include <iostream>
#include "Pool.hpp"


EntityObject *Pool::getEntity() {
    if (++currentIndex >= size) {
        std::cout << "Reached pool size" << std::endl;
        currentIndex = 0;
    }

    return _pool.at(currentIndex).get();
}
