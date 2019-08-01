#include <cstdint>
#include <vector>

#include "components/component.hpp"

#pragma once

class Bus {
public:
    Bus() {}
    explicit Bus(std::vector<Component*> components): m_components(components) {}
    uint8_t read(uint32_t loc);
    void write(uint32_t loc, uint8_t val);
private:
    std::vector<Component*> m_components;
};
