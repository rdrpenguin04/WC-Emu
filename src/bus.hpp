#include <cstdint>

#include "components/component.hpp"

#pragma once

class Bus {
public:
    Bus();
    explicit Bus(Component* *components); // 1D array of Component pointers
    uint8_t read(uint32_t loc);
    void write(uint32_t loc, uint8_t val);
};
