#include "w65c816s.hpp"

w65c816s::w65c816s(ExtBus& bus): m_bus(&bus) {
    reset();
}

void setTop8(uint16_t &reg, uint8_t val) {
    uint16_t oldPart = reg & 0x00FF;
    reg = oldPart | (uint16_t(val) << 8);
}

void w65c816s::reset() {
    m_regD = 0;
    m_regDBR = 0;
    m_regPBR = 0;
    setTop8(m_regS, 1);
    setTop8(m_regX, 0);
    setTop8(m_regY, 0);
    m_regPC = m_bus->read(0xFFFC) + (uint16_t(m_bus->read(0xFFFD)) << 8);
    m_regP &= 0xF7; // 11110111
    m_regP |= 0x34; // 00110100
    m_flagE = 1;
}
