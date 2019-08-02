#include <cstdint>

#include "bus.hpp"

#pragma once

class w65c816s {
public:
    explicit w65c816s(ExtBus bus);
    uint8_t tick(); // returns number of cycles used
    inline uint16_t getC() { return m_regC; }
    inline uint16_t getX() { return m_regX; }
    inline uint16_t getY() { return m_regY; }
    inline uint16_t getD() { return m_regD; }
    inline uint16_t getS() { return m_regS; }
    inline uint16_t getPC() { return m_regPC; }
    inline uint8_t  getDBR() { return m_regDBR; }
    inline uint8_t  getPBR() { return m_regPBR; }
    inline uint8_t  getP() { return m_regP; }
    inline uint8_t  getIR() { return m_regIR; }
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
