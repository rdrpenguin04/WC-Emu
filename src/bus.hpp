#include <cstdint>
#include <vector>
#include <initializer_list>
#include <functional>

#include "components/component.hpp"

#pragma once

class ExtBus {
public:
    explicit ExtBus(const std::initializer_list<Component*>& components): m_components{components}{}
    uint8_t read(uint32_t loc);
    void write(uint32_t loc, uint8_t val);
private:
    std::vector<Component*> m_components;
    uint8_t m_status;
};
