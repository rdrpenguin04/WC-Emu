#include <cstdint>

#include "bus.hpp"

#pragma once

class w65c816s {
public:
    explicit w65c816s(ExtBus bus);
    uint8_t tick(); // returns number of cycles used
private:
    void reset();

    ExtBus m_bus;

    uint16_t m_busAddr;
    bool     m_busAddrWritten;
    uint16_t m_busSpec;
    bool     m_busSpecWritten;
    uint16_t m_busData;
    bool     m_busDataWritten;

    uint16_t m_regX;  // Banked by DBR
    uint16_t m_regY;  // Banked by DBR
    uint16_t m_regS;  // Banked at 0
    uint16_t m_regC;  // Also includes m_regA and m_regB
    uint16_t m_regPC; // Banked by PBR
    uint16_t m_regD;  // Banked at 0
    uint8_t m_regPBR;
    uint8_t m_regDBR;
    uint8_t m_regP;
    uint8_t m_regIR;
};
